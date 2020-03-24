//
//  @(#)dump_sprite.java	2020/02/15
//
//  Image convertor for M5Stack PMPanic app.
//

import java.awt.image.BufferedImage;
import java.awt.image.IndexColorModel;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

import javax.imageio.ImageIO;

public class dump_sprite {
	static final String CRLF = "\r\n";
	static final int MAX_COLUMN = 16;
	static final int MAX_COLUMN8 = 32;

	static final boolean DEBUG = false;

	final boolean isRLE = true;
	final int RLE_REPEAT_MIN = 3;
	final int RLE_REPEAT_MAX = 127;

	final String srcFolder = "C:/Users/xxx/Dev/media/sprite/";
	final String dstFolder = "C:/Users/xxx/Dev/IoT/m5stack/projects/PMPanic/src/images/";

	final String[] bgNames = { "bg_rwanda1" }; 
	final String[] spriteNames = { "boy_idling_fine", "girl_idling_fine", "boy_walk_fine", "girl_walk_fine",
								   "boy_idling_sick", "girl_idling_sick", "boy_walk_sick", "girl_walk_sick"};
	final String[] effectNames = { "tears" };
	final String[] fontNames = { "font_36" };
	final String paletteSufix = "_pal";
	final String spriteName = "sprite";
	final int[] spritePaletteIndices = { 0, 1, 0, 1, 0, 1, 0, 1 };
	
	int PALETTE_BITS = 32; // or 16
	String PALETTE_TYPE = "uint" + PALETTE_BITS + "_t";
	
	final int HEAD_WIDTH	= 0;
	final int HEAD_HEIGHT	= 1;
	final int HEAD_COUNT	= 2;
	final int HEAD_PIVOT_X	= 3; // or font spacing
	final int HEAD_PIVOT_Y	= 4;
	
	final int SPRITE_DUP = 3;
	final boolean SPRITE_MIRROR = true;
	
	int[][] spriteHeaders = {
		{ 93, 134, 11, 0, 0 },
		{ 93, 134, 11, 0, 0 },
		{ 103, 132, 9, 0, 0 },
		{ 104, 132, 9, 0, 0 },
		{ 69, 132, 11, 0, 0 },
		{ 69, 131, 11, 0, 0 },
		{ 87, 136, 9, 0, 0 },
		{ 85, 133, 9, 0, 0 },
	};
	int[][] effectHeaders = {
		{ 6, 11, 1 }, 
	};
	int[][] fontHeaders = {
		{ 32, 0, 0, 24 }, 
	};
	int[][] spriteFrameOffsets = new int[spriteNames.length][];
	int[][] effectFrameOffsets = new int[effectNames.length][];
	int[][] fontFrameOffsets = new int[fontNames.length][];
	int maxSpriteFrames = 0;
	int maxFontFrames = 0;
	
	int[] bgPaletteCounts = new int[bgNames.length];
	int[] spritePalettes = new int[spriteNames.length];

	ArrayList<String> spritePaletteDefs = new ArrayList<String>();
	ArrayList<Integer> spritePaletteCounts =  new ArrayList<Integer>();
	
	dump_sprite() throws IOException {
		StringBuilder sb = new StringBuilder();
		sb.append("#pragma once" + CRLF);
		sb.append("#include <Arduino.h>" + CRLF);
		sb.append(CRLF);

		for (int i = 0; i < bgNames.length; i++) {
			dumpImageFile(bgNames[i], i, false, null, null);
		}		
		for (int i = 0; i < spriteNames.length; i++) {
			dumpImageFile(spriteNames[i], i, false, spriteHeaders[i], spriteFrameOffsets);
		}
		for (int i = 0; i < effectNames.length; i++) {
			dumpImageFile(effectNames[i], i, true, effectHeaders[i], effectFrameOffsets);
		}
		for (int i = 0; i < fontNames.length; i++) {
			dumpImageFile(fontNames[i], i, true, fontHeaders[i], fontFrameOffsets);
		}
		for (String name : bgNames) {
			sb.append("extern const uint8_t " + name + "[];" + CRLF);
		}
		for (String name : spriteNames) {
			sb.append("extern const uint8_t " + name + "[];" + CRLF);
		}
		for (String name : effectNames) {
			sb.append("extern const uint8_t " + name + "[];" + CRLF);
		}
		for (String name : fontNames) {
			sb.append("extern const uint8_t " + name + "[];" + CRLF);
		}
		for (String name : bgNames) {
			sb.append("extern const " + PALETTE_TYPE + " " + name + paletteSufix + "[];" + CRLF);
		}
		
		
		sb.append(CRLF);
		sb.append("#define BG_COUNT " + bgNames.length + CRLF);
		sb.append("#define SPRITE_COUNT " + spriteNames.length + CRLF);
		sb.append("#define EFFECT_COUNT " + effectNames.length + CRLF);
		sb.append("#define FONT_COUNT " + fontNames.length + CRLF);
		sb.append("#define SPRITE_MIRROR " + SPRITE_MIRROR + CRLF);
		sb.append("#define IS_RLE " + isRLE + CRLF);
		dumpVarsArray(bgNames, "uint8_t *bg_images", "", sb);
		dumpVarsArray(bgNames, PALETTE_TYPE + " *bg_palettes", paletteSufix, sb);
		dumpCountArray(bgNames, "bg_palette", bgPaletteCounts, sb);
		dumpVarsArray(spriteNames, "uint8_t *sprite_images", "", sb);
		dumpVarsArray(effectNames, "uint8_t *effect_images", "", sb);
		dumpVarsArray(fontNames, "uint8_t *font_images", "", sb);
		dumpHeaders(spriteHeaders, "Sprite", sb);
		dumpFrameOffsets(spriteFrameOffsets, maxSpriteFrames, "sprite", sb);
		for (String spritePaletteDef : spritePaletteDefs) {
			sb.append(CRLF);
			sb.append(spritePaletteDef);
		}
		sb.append(CRLF);
		sb.append("const uint8_t sprite_palette_indices[] = { ");
		for (int i = 0; i < spritePaletteIndices.length; i++) {
			sb.append(spritePaletteIndices[i]);
			if (i < spritePaletteIndices.length - 1) {
				sb.append(", ");
			}
		}
		sb.append(" };" + CRLF);
		sb.append("const " + PALETTE_TYPE +  " *sprite_palettes[] = { ");
		for (int i = 0; i < spritePaletteDefs.size(); i++) {
			sb.append(spriteName + i + paletteSufix);
			if (i < spritePaletteDefs.size() - 1) {
				sb.append(", ");
			}
		}
		sb.append(" };" + CRLF);
		sb.append("const uint8_t sprite_palette_counts[] = { ");
		for (int i = 0; i < spritePaletteCounts.size(); i++) {
			sb.append(spritePaletteCounts.get(i));
			if (i < spritePaletteDefs.size() - 1) {
				sb.append(", ");
			}
		}
		sb.append(" };" + CRLF);

		dumpHeaders(effectHeaders, "Effect", sb);
		dumpFrameOffsets(effectFrameOffsets, 1, "Effect", sb); // TODO
		dumpHeaders(fontHeaders, "Font", sb);
		dumpFrameOffsets(fontFrameOffsets, maxFontFrames, "font", sb);

		if (!DEBUG) {
			System.out.println(sb.toString());
	
			BufferedWriter bw = new BufferedWriter(new FileWriter(new File(dstFolder + "images.h")));
			bw.write(sb.toString());
			bw.close();
		}
		System.out.println("done.");
	}
	
	void dumpVarsArray(String[] imageNames, String varName, String varSuffix, StringBuilder sb) {
		sb.append(CRLF);
		sb.append("const " + varName + "[] = { ");
		for (int i = 0; i < imageNames.length; i++) {
			sb.append(imageNames[i] + varSuffix);
			if (i < imageNames.length - 1) {
				sb.append(", ");
			}
		}
		sb.append(" };" + CRLF);
	}

	void dumpCountArray(String[] imageNames, String varName, int[] paletetCounts, StringBuilder sb) {
		sb.append(CRLF);
		sb.append("const uint8_t " + varName + "_counts[] = { ");
		for (int i = 0; i < imageNames.length; i++) {
			sb.append(paletetCounts[i]);
			if (i < imageNames.length - 1) {
				sb.append(", ");
			}
		}
		sb.append(" };" + CRLF);
	}
	
	void dumpHeaders(int[][] headers, String varName, StringBuilder sb) {
		sb.append(CRLF);
		sb.append("struct " + varName +"Header {" + CRLF);
		sb.append("\tuint8_t width;" + CRLF);
		sb.append("\tuint8_t height;" + CRLF);
		sb.append("\tuint8_t count;" + CRLF);
		if (varName.equals("Sprite")) {
			sb.append("\tuint8_t pivotX;" + CRLF);
			sb.append("\tuint8_t pivotY;" + CRLF);
		} else if (varName.equals("Font")) {
			sb.append("\tuint8_t spacing;" + CRLF);
		}
		sb.append("};" + CRLF);
		sb.append("const " + varName + "Header " + varName.toLowerCase() + "_headers[] = {" + CRLF);
		for (int[] header : headers) {
			sb.append("\t{ ");
			for (int j = 0; j < header.length; j++) {
				sb.append(header[j]);
				if (j < header.length - 1) {
					sb.append(", ");
				}
			}
			sb.append(" }," + CRLF);
		}
		sb.append("};" + CRLF);
	}
	
	void dumpFrameOffsets(int[][] frameOffsets, int maxFrames, String varName, StringBuilder sb) {
		sb.append("const uint32_t " + varName + "_frame_offsets[" + frameOffsets.length + "][" + maxFrames + "] {" + CRLF);
		for (int[] arr : frameOffsets) {
			sb.append("\t{ ");
			for (int i = 0; i < maxFrames; i++) {
				int n = (i < arr.length) ? arr[i] : 0;
				sb.append(n + ", ");
			}
			sb.append("}," + CRLF);
		}
		sb.append("};" + CRLF);
	}

	void dumpImageFile(String name, int index, boolean isFont, int[] header, int[][] frameOffsets) throws IOException {
		String text = dumpImage(name, index, isFont, header, frameOffsets);
		
		if (!DEBUG) {
			System.out.println(text);
	
			BufferedWriter bw = new BufferedWriter(new FileWriter(new File(dstFolder + name + ".c")));
			bw.write(text);
			bw.close();
		}
	}

	
	String dumpImage(String name, int index, boolean isFont, int[] header, int[][] frameOffsetsArray) throws IOException {
		String srcPath = srcFolder + name + ".png";
		File file = new File(srcPath);
		BufferedImage bi = ImageIO.read(file);
		IndexColorModel icm = (IndexColorModel)bi.getColorModel();
		
		int tpIndex = icm.getTransparentPixel();
		boolean isSprite = tpIndex != -1;

		int frameOffset = 0;
		int[] frameOffsets = null;
		
		int width = bi.getWidth();
		int height = bi.getHeight();
		int cellWidth = isSprite ? header[HEAD_WIDTH] : width;
		int cellHeight = (isSprite && !isFont) ? header[HEAD_HEIGHT] : height;
		int cellCount = isSprite ? (isFont ? (width / cellWidth) : header[HEAD_COUNT]) : 1;
		if (isSprite) {
			if (isFont) {
				header[HEAD_HEIGHT] = cellHeight;
				header[HEAD_COUNT] = cellCount;
			}
			if (isRLE) {
				frameOffsets = frameOffsetsArray[index] = new int[cellCount];
				if (isFont) {
					if (cellCount > maxFontFrames) {
						maxFontFrames = cellCount;
					}
				} else {
					if (cellCount > maxSpriteFrames) {
						maxSpriteFrames = cellCount;
					}
				}
			}
		}

		StringBuilder sb = new StringBuilder();
		sb.append("const uint8_t " + name + "[] = {" + CRLF);

		int[] pixels = bi.getData().getPixels(0, 0, width, height, (int[])null);
		int maxPalette = -1;
		
		int cellX = 0;
		int cellY = 0;
		for (int cell = 0; cell < cellCount; cell++) {
			sb.append("// #" + cell + CRLF);
			int col = 0;
			int cellBytes = 0;
			for (int y = 0; y < cellHeight; y++) {
				int[] line = new int[cellWidth];
				for (int x = 0; x < cellWidth; x++) {
					int idx = pixels[x + cellX * cellWidth + (y + cellY * cellHeight) * width];
					if (idx > maxPalette) {
						maxPalette = idx;
					}
					if (tpIndex != -1) {
						if (idx == tpIndex) {
							idx = 0;
						} else if (idx == 0) {
							idx = tpIndex;
						}
					}
					line[x] = idx;
				}
				int[] line1 = isRLE ? encodeRLE(line) : line;
				cellBytes += line1.length;
				for (int i = 0; i < line1.length; i++) {
					if (col == 0) {
						sb.append("\t");
					}
					sb.append(line1[i] + ", ");
					if (++col >= MAX_COLUMN8) {
						col = 0;
						sb.append(CRLF);
					}
				}
				if (DEBUG) {
					int[] line2 = decodeRLE(line1);
					if (!Arrays.equals(line, line2)) {
						System.out.println("*** mistmatched line " + y);
						System.out.print("[" + line.length + "] ");
						for (int i = 0; i < line.length; i++) {
							System.out.print(line[i] + ",");
						}
						System.out.println("");
						System.out.print("[" + line2.length + "] ");
						for (int i = 0; i < line2.length; i++) {
							System.out.print(line2[i] + ",");
						}						
						System.out.println("");
						System.out.print("--> [" + line1.length + "] ");
						for (int i = 0; i < line1.length; i++) {
							System.out.print(line1[i] + ",");
						}						
						System.out.println("");
					}
				}
			}
			sb.append(CRLF);
			if (isRLE && isSprite) {
				frameOffsets[cell] = frameOffset;
				frameOffset += cellBytes;
			}
			int skipCount = (isSprite && !isFont) ? SPRITE_DUP : 1;
			for (int n = 0; n < skipCount; n++) {
				if (++cellX * cellWidth > (width - cellWidth)) {
					cellX = 0;
					cellY++;
				}
			}
		}
		sb.append("};" + CRLF);

		StringBuilder sbPal = new StringBuilder();
		if (!isSprite) {
			dumpPalette(icm, maxPalette, name + paletteSufix, sbPal);
			sb.insert(0, sbPal);
			bgPaletteCounts[index] = maxPalette + 1;
		} else {
			int palIndex = spritePaletteIndices[index];
			if (spritePaletteDefs.size() <= palIndex) {
				dumpPalette(icm, maxPalette, spriteName + palIndex + paletteSufix, sbPal);
				spritePaletteDefs.add(sbPal.toString());
				spritePaletteCounts.add(maxPalette + 1);
			}
		}
		sb.insert(0, "#include <Arduino.h>" + CRLF + CRLF);
		return sb.toString();
	}
	
	void dumpPalette(IndexColorModel icm, int maxPalette, String varName, StringBuilder sb) {
		sb.append("const " + PALETTE_TYPE + " " + varName + "[] = {" + CRLF);

		int[] palette = new int[icm.getMapSize()];
		icm.getRGBs(palette);
		int tpIndex = icm.getTransparentPixel();
		int paletteCount = maxPalette + 1;

		int tpRGB = -1;
		for (int i = 0; i < paletteCount; i++) {
			int rgb = palette[i] & 0xFFFFFF;
			if (i == 0 && tpIndex > 0) {
				tpRGB = rgb;
				rgb = 0;
			}
			if (i == tpIndex) {
				rgb = tpRGB;
			}
			if ((i % MAX_COLUMN) == 0) {
				sb.append("\t");
			}
			if (PALETTE_BITS == 32) {
				sb.append(String.format("0x%06X,", rgb));
			} else { // 16
				sb.append(String.format("0x%04X,", color32To16(rgb)));
			}
			if ((i % MAX_COLUMN) == MAX_COLUMN - 1) {
				sb.append(CRLF);
			}
		}
		if ((paletteCount % MAX_COLUMN) != 0) {
			sb.append(CRLF);
		}
		sb.append("};" + CRLF);
	}
	
	int[] encodeRLE(int[] src) {
		ArrayList<Integer> dest = new ArrayList<Integer>();
		int m = 0;
		int c = 0;
		int j = 0;
		for (int i = 0; i < src.length + 1; i++) {
			int n = i < src.length ? src[i] : -1;
			if (i == 0) {
				m = n;
			} else if (n == m && c < RLE_REPEAT_MAX) {
				c++;
			} else {
				if (c >= RLE_REPEAT_MIN || n == -1) {
					int j1 = i - c - 1;
					if (j1 > j) {
						dest.add(j1 - j - 1);
						while (j < j1) {
							dest.add(src[j++]);
						}
					}
					dest.add(c | 0x80);
					dest.add(m);
					j = i;
				}
				c = 0;
				m = n;
			}
		}
		return toIntArray(dest);
	}
	
	int[] decodeRLE(int[] src) {
		ArrayList<Integer> dest = new ArrayList<Integer>();
		int i = 0;
		while (i < src.length) {
			int b = src[i++];
			int c = b & 0x7F;
			if ((b & 0x80) != 0) {
				b = src[i++];
				for (int j = 0; j < c + 1; j++) {
					dest.add(b);
				}
			} else {
				for (int j = 0; j < c + 1; j++) {
					dest.add(src[i++]);
				}
			}
		}
		return toIntArray(dest);
	}
	
	int[] toIntArray(ArrayList<Integer> list) {
		int[] arr = new int[list.size()];
		for (int i = 0; i < list.size(); i++) {
			arr[i] = list.get(i);
		}
		return arr;
	}

	static int color32To16(int rgb) {
		return color565((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
	}
	
	static int color565(int r, int g, int b) {
		return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
	}
	
	public static void main(String[] args) throws IOException {
		new dump_sprite();
		
//		System.out.println(String.format("%04X", color565(255,255,204)));
	
/*		if (args.length == 0) {
			System.out.println("usage: java -jar dump_image.jar <image file path> [<var name>]");
		} else {
			String path = args[0];
			String varName =  (args.length >= 2) ? args[1] : null;
			System.out.print(dumpImage(path, varName));
		}
*/
	}
}
