/*
  ==============================================================================

	PatternLayer.cpp
	Created: 30 Jun 2021 2:01:26pm
	Author:  bkupe

  ==============================================================================
*/

#include "PatternLayer.h"
#include "PatternClip.h"
#include "ui/PatternLayerPanel.h"
#include "ui/PatternLayerTimeline.h"
#include "Library/PicturePattern.h"
#include "Library/ColorPattern.h"

PatternLayer::PatternLayer(Sequence* sequence, var params) :
	SequenceLayer(sequence, getTypeString()),
	clipManager(this)
{
	propType = addEnumParameter("Prop Type", "Type of the prop this layer is made for");
	propType->addOption("Ball", BALL)->addOption("Hoop", HOOP)->addOption("144 Pixels", PIXEL144)->addOption("64 Pixels", PIXEL64)->addOption("32 Pixels", PIXEL32)->addOption("Custom", CUSTOM);
	numPixels = addIntParameter("Num Pixels", "Resolution of the prop.", 32, 1, 16000, false);
	refreshRate = addIntParameter("Refresh Rate", "Refresh Rate for the prop", 1000, 1, 16000, false);
	exportToPRG = addTrigger("Export to PRG", "Export the sequence to PRG file");

	saveAndLoadRecursiveData = true;
	addChildControllableContainer(&clipManager);
}

PatternLayer::~PatternLayer()
{
}


void PatternLayer::onContainerParameterChangedInternal(Parameter* p)
{
	if (p == propType)
	{
		numPixels->setEnabled(propType->getValueDataAsEnum<PropType>() == CUSTOM);
		refreshRate->setEnabled(propType->getValueDataAsEnum<PropType>() == CUSTOM);
	}
}

void PatternLayer::onContainerTriggerTriggered(Trigger* t)
{
	if (t == exportToPRG)
	{
		exportLayer();
	}
}

void PatternLayer::exportLayer()
{
	int nPixels = 32;
	int refresh = 1000;
	
	PropType t = propType->getValueDataAsEnum<PropType>();
	
	switch (t)
	{
	case BALL: 
		nPixels = 4;
		refresh = 1000;
		break;

	case HOOP:
		nPixels = 250;
		refresh = 625;
		break;

	case PIXEL144:
		nPixels = 144;
		refresh = 1818;
		break;

	case PIXEL64:
		nPixels = 64;
		refresh = 1000;
		break;
	
	case PIXEL32:
		nPixels = 32;
		refresh = 1000;
		break;

	case CUSTOM:
		nPixels = numPixels->intValue();
		refresh = refreshRate->intValue();
		break;
	}

	File f = Engine::mainEngine->getFile();
	File folder = f.existsAsFile() ? f.getParentDirectory() : File::getSpecialLocation(File::userDesktopDirectory);
	File file = folder.getChildFile((f.existsAsFile() ? f.getFileNameWithoutExtension() + " - " : "") + niceName + ".prg");

	MemoryBlock b;
	MemoryOutputStream os(b, false);

	//Header
	os.writeByte(0x50);
	os.writeByte(0x52);
	os.writeByte(0x03);

	//Info Block
	os.writeByte(0x49);
	os.writeByte(0x4E);
	os.writeInt(5);
	os.writeShort(nPixels);
	os.writeByte(8);
	os.writeShort(refresh);

	//Pattern index block
	os.writeByte(0x50);
	os.writeByte(0x49);

	Array<PatternClip*> clips = getValidClips();
	
	MemoryBlock dataBlocks;
	MemoryOutputStream dos(dataBlocks, false);

	int piBlockLength = 2 + clips.size() * 19;
	os.writeInt(piBlockLength);
	os.writeShort(clips.size());

	LOG("Size before patterns " << os.getDataSize());

	int dataBlockStartPos = os.getDataSize() + clips.size() * 19 +10; //+10 because pointer is on the actual rgb data and not the block data
	for (auto& clip : clips)
	{
		int repeatHorizontal = 1;
		int rowCount = 1;
		int repeatVertical = 1;
		int absFilePosition = dataBlockStartPos + (int)dos.getDataSize();
		bool mirrorV = false;

		int columnCount = 1;
		//int scaleFactor = 1;

		float clipLength = clip->getTotalLength();
		int totalColumnCount = 1;

		if (PicturePattern* pp = dynamic_cast<PicturePattern*>(clip->pattern))
		{
			
			repeatHorizontal = clip->patternParams.getParameterByName(pp->horizontalRepetitions->shortName)->intValue();
			repeatVertical = clip->patternParams.getParameterByName(pp->verticalRepetitions->shortName)->intValue();
			float patternLength = clipLength / repeatHorizontal; //in seconds
			columnCount = patternLength * refresh;
			rowCount = jmax(nPixels / repeatVertical, 1);
			mirrorV = clip->patternParams.getParameterByName(pp->mirrorV->shortName)->boolValue();


			//write image
			File imgFile = ((FileParameter*)clip->patternParams.getParameterByName(pp->file->shortName))->getFile();
			Image img = ImageCache::getFromFile(imgFile).rescaled(columnCount, rowCount);
			int blockDataSize = 4 + img.getWidth() + img.getHeight();
			
			dos.writeByte(0x43);
			dos.writeByte(0x44);
			dos.writeInt(blockDataSize);
			dos.writeInt(columnCount);

			for (int i = 0; i < columnCount; i++)
			{
				for (int j = 0; j < rowCount; j++)
				{
					Colour c = img.getPixelAt(i, j);
					dos.writeByte(c.getRed());
					dos.writeByte(c.getGreen());
					dos.writeByte(c.getBlue());
				}
			}
		}
		else if (ColorPattern* cp = dynamic_cast<ColorPattern*>(clip->pattern))
		{
			columnCount = 1;
			repeatHorizontal = clipLength * refresh;
			rowCount = nPixels;
			repeatVertical = nPixels;
			mirrorV = false;

			Colour c = ((ColorParameter *)clip->patternParams.getParameterByName(cp->color->shortName))->getColor();
			
			dos.writeByte(0x43);
			dos.writeByte(0x44);
			dos.writeInt(4 + 3);// *nPixels); //only 3 bytes for r,g,b
			dos.writeInt(columnCount);
			//for (int i = 0; i < nPixels; i++)
			//{
				
				dos.writeByte(c.getRed());
				dos.writeByte(c.getGreen());
				dos.writeByte(c.getBlue());
			//}
			
		}

		totalColumnCount = columnCount * repeatHorizontal;

		os.writeShort(repeatHorizontal);
		os.writeShort(columnCount);
		os.writeInt(absFilePosition);
		os.writeShort(0); //fractional rest num columns if not perfect loops. for now 0 as repeat horizontal is integer
		os.writeShort(repeatVertical);
		os.writeShort(rowCount);
		os.writeByte(mirrorV ? 1 : 0);
		os.writeInt(totalColumnCount);

		LOG(" > abs pos " << absFilePosition << " / pi " << os.getDataSize());

	}

	LOG("Start writing blocks at " << os.getDataSize());
	//write blocks
	os.write(dataBlocks.getData(), dataBlocks.getSize());


	if (file.existsAsFile()) file.deleteFile();
	FileOutputStream fs(file);
	fs.write(b.getData(), b.getSize());
	fs.flush();

	LOG("File exported to " + file.getFullPathName());
}


Array<PatternClip*> PatternLayer::getValidClips()
{
	Array<PatternClip*> result;
	for (auto& clip : clipManager.items)
	{
		PatternClip* p = (PatternClip*)clip;
		if (p->pattern == nullptr) continue;
		if (PicturePattern* pp = dynamic_cast<PicturePattern*>(p->pattern))
		{
			File f = ((FileParameter*)p->patternParams.getParameterByName(pp->file->shortName))->getFile();
			if (!f.existsAsFile()) continue;
		}
		result.add(p);
	}

	return result;
}

SequenceLayerPanel* PatternLayer::getPanel()
{
	return new PatternLayerPanel(this);
}

SequenceLayerTimeline* PatternLayer::getTimelineUI()
{
	return new PatternLayerTimeline(this);
}

PatternClipManager::PatternClipManager(PatternLayer* layer) :
	LayerBlockManager(layer, "Patterns"),
	patternLayer(layer)
{
	blocksCanOverlap = false;
}

LayerBlock* PatternClipManager::createItem()
{
	return new PatternClip();
}
