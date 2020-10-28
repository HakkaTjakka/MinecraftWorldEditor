/*
 *  This file is part of CubicChunksConverter, licensed under the MIT License (MIT).
 *
 *  Copyright (c) 2017 contributors
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
package cubicchunks.converter.lib.convert.cc2anvil;

import static cubicchunks.converter.lib.util.Utils.readCompressedCC;
import static cubicchunks.converter.lib.util.Utils.writeCompressed;

import com.flowpowered.nbt.ByteTag;
import com.flowpowered.nbt.CompoundMap;
import com.flowpowered.nbt.CompoundTag;
import com.flowpowered.nbt.IntArrayTag;
import com.flowpowered.nbt.IntTag;
import com.flowpowered.nbt.ListTag;
import com.flowpowered.nbt.Tag;
import cubicchunks.converter.lib.conf.ConverterConfig;
import cubicchunks.converter.lib.convert.ChunkDataConverter;
import cubicchunks.converter.lib.convert.data.AnvilChunkData;
import cubicchunks.converter.lib.convert.data.CubicChunksColumnData;
import cubicchunks.converter.lib.convert.data.MultilayerAnvilChunkData;
import cubicchunks.regionlib.impl.MinecraftChunkLocation;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.EOFException;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.*;
import java.util.zip.ZipException;

import javax.annotation.Nullable;

public class CC2AnvilDataConverter implements ChunkDataConverter<CubicChunksColumnData, MultilayerAnvilChunkData> {

    @Override public Set<MultilayerAnvilChunkData> convert(CubicChunksColumnData input) {
        Map<Integer, AnvilChunkData> data = new HashMap<>();
        MinecraftChunkLocation chunkPos = new MinecraftChunkLocation(input.getPosition().getEntryX(), input.getPosition().getEntryZ(), "mca");

        // split the data into world layers
        Map<Integer, ByteBuffer[]> worldLayers = new HashMap<>();
        input.getCubeData().forEach((key, value) -> {
            ByteBuffer[] sections = worldLayers.computeIfAbsent(toWorldLayerY(key), y -> new ByteBuffer[16]);
            sections[toLayerSection(key)] = value;
        });
        // convert each world layer separately
        worldLayers.forEach((key, value) ->
            data.put(key, new AnvilChunkData(input.getDimension(), chunkPos, convertWorldLayer(input.getColumnData(), value, key)))
        );
        return Collections.singleton(new MultilayerAnvilChunkData(data));
    }

    private ByteBuffer convertWorldLayer(@Nullable ByteBuffer columnData, ByteBuffer[] cubes, int layerIdx) {
        try {
            if (dropChunk(cubes, layerIdx)) {
                return null;
            }
            CompoundTag columnTag = columnData == null ? null : readCompressedCC(new ByteArrayInputStream(columnData.array()));
            CompoundTag[] cubeTags = new CompoundTag[cubes.length];
            for (int i = 0; i < cubes.length; i++) {
                if (cubes[i] != null) {
                    cubeTags[i] = readCompressedCC(new ByteArrayInputStream(cubes[i].array()));
                }
            }
            CompoundTag tag = convertWorldLayer(columnTag, cubeTags, layerIdx);
            return writeCompressed(tag, true);
        } catch (ZipException e) {
            e.printStackTrace();
            return null;
        } catch (IOException e) {
            throw new Error("ByteArrayInputStream doesn't throw IOException", e);
        }
    }

    private boolean dropChunk(ByteBuffer[] cubes, int layerIdx) {
        return false;
    }

    private CompoundTag convertWorldLayer(@Nullable CompoundTag column, CompoundTag[] cubes, int layerIdx) {
        /*
         *
         * Vanilla Chunk NBT structure:
         *
         * ROOT
         * |- DataVersion
         * |- Level
         *  |- v
         *  |- xPos
         *  |- zPos
         *  |- LastUpdate
         *  |- TerrainPopulated
         *  |- LightPopulated
         *  |- InhabitedTime
         *  |- Biomes
         *  |- HeightMap
         *  |- Sections
         *  ||* Section list:
         *  | |- Y
         *  | |- Blocks
         *  | |- Data
         *  | |- Add
         *  | |- BlockLight
         *  | |- SkyLight
         *  |- Entities
         *  |- TileEntities
         *  |- TileTicks
         *
         * CubicChunks Column format:
         *
         * ROOT
         * |- DataVersion
         * |- Level
         *  |- v
         *  |- x
         *  |- z
         *  |- InhabitedTime
         *  |- Biomes
         *  |- OpacityIndex
         */
        CompoundMap vanillaMap = new CompoundMap();
        // TODO: we expect DataVersion to be the same as column for all cubes, this is not necessarily true. Can we do something about it?
        if (column != null) {
            for (Tag<?> tag : column.getValue()) {
                if ("Level".equals(tag.getName())) {
                    CompoundMap level = new CompoundMap();
                    convertLevel(level, column, cubes, layerIdx);
                    vanillaMap.put(new CompoundTag("Level", level));
                } else {
                    vanillaMap.put(tag);
                }
            }
        } else {
            CompoundMap level = new CompoundMap();
            convertLevel(level, null, cubes, layerIdx);
            vanillaMap.put(new CompoundTag("Level", level));
        }

        return new CompoundTag("", vanillaMap);

    }

    private void convertLevel(CompoundMap level, @Nullable CompoundTag column, CompoundTag[] cubes, int layerIdx) {
        /*
         *
         * Vanilla Chunk NBT structure:
         *
         * ROOT
         * |- DataVersion
         * |- Level
         *  |- v
         *  |- xPos
         *  |- zPos
         *  |- LastUpdate
         *  |- TerrainPopulated
         *  |- LightPopulated
         *  |- InhabitedTime
         *  |- Biomes
         *  |- HeightMap
         *  |- Sections
         *  ||* Section list:
         *  | |- Y
         *  | |- Blocks
         *  | |- Data
         *  | |- Add
         *  | |- BlockLight
         *  | |- SkyLight
         *  |- Entities
         *  |- TileEntities
         *  |- TileTicks
         *
         * CubicChunks Cube NBT structure:
         *
         * ROOT
         * |- DataVersion
         * |- Level
         *  |- v
         *  |- x
         *  |- y
         *  |- z
         *  |- populated
         *  |- fullyPopulated
         *  |- initLightDone
         *  |- Sections
         *  ||* A single section
         *  | |- Blocks
         *  | |- Data
         *  | |- Add
         *  | |- BlockLight
         *  | |- SkyLight
         *  |- Entities
         *  |- TileEntities
         *  |- TileTicks
         *  |- LightingInfo
         *   |- LastHeightMap
         */
        if (column != null) {
            CompoundMap columnLevel = (CompoundMap) column.getValue().get("Level").getValue();
            for (Tag<?> tag : columnLevel) {
                switch (tag.getName()) {
                    case "x":
                        level.put(renamedInt(tag, "xPos"));
                        break;
                    case "z":
                        level.put(renamedInt(tag, "zPos"));
                        break;
                    case "OpacityIndex":
                        level.put(getHeightMap(tag, layerIdx));
                        break;
                    default:
                        level.put(tag);
                }
            }
        }
        // TODO: use existing heightmap? Is it safe?
        int[] heights = new int[256];
        Arrays.fill(heights, -999);
        Tag<?> heightsTag = new IntArrayTag("HeightMap", heights);
        level.put(heightsTag);

        for (CompoundTag cube : cubes) {
            if (cube != null) {
                CompoundTag cubeLevel = (CompoundTag) cube.getValue().get("Level");
                for (Tag<?> tag : cubeLevel.getValue()) {
                    switch (tag.getName()) {
                        case "x":
                            level.put(renamedInt(tag, "xPos"));
                            break;
                        case "z":
                            level.put(renamedInt(tag, "zPos"));
                            break;
                    }
                }
                break;
            }
        }

        level.put(getIsPopulated(cubes, layerIdx));
        level.put(new ByteTag("LightPopulated", (byte) 1)); // can't let vanilla recalculate lighting because 1.14.x drops such chunks :(

        level.put(getSections(cubes));
        level.put(getEntities(cubes));
        level.put(getTileEntities(cubes));
        level.put(getTileTicks(cubes));
    }

    private Tag<?> getSections(CompoundTag[] cubes) {
        List<CompoundTag> sections = new ArrayList<>();
        for (int y = 0; y < cubes.length; y++) {
            if (cubes[y] == null) {
                continue;
            }
            CompoundMap oldLevel = (CompoundMap) cubes[y].getValue().get("Level").getValue();
            if (oldLevel.get("Sections") == null) {
                continue;
            }
            CompoundMap newSection = new CompoundMap();
            @SuppressWarnings("unchecked")
            List<CompoundTag> oldSections = (List<CompoundTag>) oldLevel.get("Sections").getValue();
            CompoundMap oldSection = oldSections.get(0).getValue();
            newSection.putAll(oldSection);
            newSection.put(new ByteTag("Y", (byte) y));
            sections.add(new CompoundTag("", newSection));
        }
        return new ListTag<>("Sections", CompoundTag.class, sections);
    }

    private Tag<?> getEntities(CompoundTag[] cubes) {
        return new ListTag<>("Entities", CompoundTag.class, new ArrayList<>());
    }

    private Tag<?> getTileEntities(CompoundTag[] cubes) {
        return new ListTag<>("TileEntities", CompoundTag.class, new ArrayList<>());
    }

    private Tag<?> getTileTicks(CompoundTag[] cubes) {
        return new ListTag<>("TileTicks", CompoundTag.class, new ArrayList<>());
    }

    private Tag<?> getIsPopulated(CompoundTag[] cubes, int layerIdx) {
        // with default world, only those cubes really matter
        for (int y = 0; y < 8; y++) {
            if (cubes[y] == null) {
                return new ByteTag("TerrainPopulated", (byte) 0);
            }
            CompoundMap map = (CompoundMap) cubes[y].getValue().get("Level").getValue();
            if ((Byte) map.get("populated").getValue() == 0) {
                return new ByteTag("TerrainPopulated", (byte) 0);
            }
        }
        return new ByteTag("TerrainPopulated", (byte) 1);
    }

    private Tag<?> getHeightMap(Tag<?> opacityIndex, int layerIdx) {
        byte[] array = (byte[]) opacityIndex.getValue();
        int[] output = new int[256];
        ByteArrayInputStream buf = new ByteArrayInputStream(array);
        try (DataInputStream in = new DataInputStream(buf)) {

            for (int i = 0; i < output.length; i++) {
                in.readInt(); // yMin
                output[i] = (in.readInt() + 1) - (layerIdx * 256);
                int segmentCount = in.readUnsignedShort();
                for (int j = 0; j < segmentCount; j++) {
                    in.readInt();
                }
            }
        } catch (EOFException e) {
            e.printStackTrace();
            Arrays.fill(output, -999);
        } catch (IOException e) {
            throw new Error("ByteArrayInputStream doesn't throw IOException");
        }
        return new IntArrayTag("HeightMap", output);
    }

    private IntTag renamedInt(Tag<?> old, String newName) {
        return new IntTag(newName, (Integer) old.getValue());
    }

    @Override public ConverterConfig getConfig() {
        return new ConverterConfig(new HashMap<>());
    }

    private static int toWorldLayerY(int cubeY) {
        return cubeY >> 4;
    }

    private static int toLayerSection(int cubeY) {
        return cubeY & 0xF;
    }
}
