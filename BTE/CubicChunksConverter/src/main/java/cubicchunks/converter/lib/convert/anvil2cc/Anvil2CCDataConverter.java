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
package cubicchunks.converter.lib.convert.anvil2cc;

import static java.util.Collections.emptyList;
import static java.util.Collections.singletonList;

import com.flowpowered.nbt.ByteArrayTag;
import com.flowpowered.nbt.ByteTag;
import com.flowpowered.nbt.CompoundMap;
import com.flowpowered.nbt.CompoundTag;
import com.flowpowered.nbt.DoubleTag;
import com.flowpowered.nbt.IntArrayTag;
import com.flowpowered.nbt.IntTag;
import com.flowpowered.nbt.ListTag;
import cubicchunks.converter.lib.util.Utils;
import cubicchunks.converter.lib.convert.data.AnvilChunkData;
import cubicchunks.converter.lib.convert.data.CubicChunksColumnData;
import cubicchunks.converter.lib.convert.ChunkDataConverter;
import cubicchunks.regionlib.impl.EntryLocation2D;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.*;

public class Anvil2CCDataConverter implements ChunkDataConverter<AnvilChunkData, CubicChunksColumnData> {

    public Set<CubicChunksColumnData> convert(AnvilChunkData input) {
        try {
            Map<Integer, ByteBuffer> cubes = extractCubeData(input.getData());
            ByteBuffer column = extractColumnData(input.getData());
            EntryLocation2D location = new EntryLocation2D(input.getPosition().getEntryX(), input.getPosition().getEntryZ());
            return Collections.singleton(new CubicChunksColumnData(input.getDimension(), location, column, cubes));
        } catch (IOException impossible) {
            throw new Error("ByteArrayInputStream doesn't throw IOException", impossible);
        }
    }


    private ByteBuffer extractColumnData(ByteBuffer vanillaData) throws IOException {
        ByteArrayInputStream in = new ByteArrayInputStream(vanillaData.array());
        CompoundTag tag = Utils.readCompressed(in);
        CompoundTag columnTag = extractColumnData(tag);
        return Utils.writeCompressed(columnTag, false);
    }

    private CompoundTag extractColumnData(CompoundTag tag) throws IOException {
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
        CompoundMap levelMap = new CompoundMap();
        CompoundMap srcLevel = (CompoundMap) tag.getValue().get("Level").getValue();

        int[] srcHeightMap = fixHeightmap((int[]) srcLevel.get("HeightMap").getValue());

        levelMap.put(new IntTag("v", 1));
        levelMap.put(new IntTag("x", (Integer) srcLevel.get("xPos").getValue()));
        levelMap.put(new IntTag("z", (Integer) srcLevel.get("zPos").getValue()));
        levelMap.put(srcLevel.getOrDefault("InhabitedTime", new IntTag("InhabitedTime", 0)));
        levelMap.put(srcLevel.get("Biomes"));
        levelMap.put(new ByteArrayTag("OpacityIndex", makeDummyOpacityIndex(srcHeightMap)));

        CompoundMap rootMap = new CompoundMap();
        rootMap.put(new CompoundTag("Level", levelMap));
        if (tag.getValue().containsKey("DataVersion")) {
            rootMap.put(tag.getValue().get("DataVersion"));
        }

        return new CompoundTag("", rootMap);
    }

    private int[] fixHeightmap(int[] heights) {
        for (int i = 0; i < heights.length; i++) {
            heights[i]--; // vanilla = 1 above top, data = top block
        }
        return heights;
    }

    private byte[] makeDummyOpacityIndex(int[] heightMap) throws IOException {
        ByteArrayOutputStream buf = new ByteArrayOutputStream();
        DataOutputStream out = new DataOutputStream(buf);

        for (int i = 0; i < 256; i++) { // 256 segment arrays
            out.writeInt(0); // minY
            out.writeInt(heightMap[i]); // maxY
            out.writeShort(0); // no segments - write zero
        }

        out.close();
        return buf.toByteArray();
    }

    private Map<Integer, ByteBuffer> extractCubeData(ByteBuffer vanillaData) throws IOException {
        ByteArrayInputStream in = new ByteArrayInputStream(vanillaData.array());
        Map<Integer, CompoundTag> tags = extractCubeData(Utils.readCompressed(in));
        Map<Integer, ByteBuffer> bytes = new HashMap<>();
        for (Integer y : tags.keySet()) {
            bytes.put(y, Utils.writeCompressed(tags.get(y), false));
        }
        return bytes;
    }

    @SuppressWarnings("unchecked")
    private Map<Integer, CompoundTag> extractCubeData(CompoundTag srcRootTag) {
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
         *  |- isSurfaceTracked
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
        CompoundMap srcRoot = srcRootTag.getValue();
        Map<Integer, CompoundTag> tags = new HashMap<>();
        CompoundMap srcLevel = ((CompoundTag) srcRoot.get("Level")).getValue();
        int x = (Integer) srcLevel.get("xPos").getValue();
        int z = (Integer) srcLevel.get("zPos").getValue();
        //noinspection unchecked
        for (CompoundTag srcSection : ((ListTag<CompoundTag>) srcLevel.get("Sections")).getValue()) {
            int y = ((ByteTag) srcSection.getValue().get("Y")).getValue();

            CompoundMap root = new CompoundMap();
            {
                if (srcRoot.containsKey("DataVersion")) {
                    root.put(srcRoot.get("DataVersion"));
                }
                CompoundMap level = new CompoundMap();

                {
                    level.put(new ByteTag("v", (byte) 1));
                    level.put(new IntTag("x", x));
                    level.put(new IntTag("y", y));
                    level.put(new IntTag("z", z));

                    ByteTag populated = (ByteTag) srcLevel.get("TerrainPopulated");
                    level.put(new ByteTag("populated", populated == null ? 0 : populated.getValue()));
                    level.put(new ByteTag("fullyPopulated", populated == null ? 0 : populated.getValue())); // TODO: handle this properly
                    level.put(new ByteTag("isSurfaceTracked", (byte) 0)); // so that cubic chunks can re-make surface tracking data on it's own

                    ByteTag lightPopulated = (ByteTag) srcLevel.get("LightPopulated");
                    level.put(new ByteTag("initLightDone", lightPopulated == null ? 0 : lightPopulated.getValue()));

                    // the vanilla section has additional Y tag, it will be ignored by cubic chunks
                    level.put(new ListTag<>("Sections", CompoundTag.class, singletonList(fixSection(srcSection))));

                    level.put(filterEntities((ListTag<CompoundTag>) srcLevel.get("Entities"), y));
                    level.put(filterTileEntities((ListTag<?>) srcLevel.get("TileEntities"), y));
                    if (srcLevel.containsKey("TileTicks")) {
                        level.put(filterTileTicks((ListTag<CompoundTag>) srcLevel.get("TileTicks"), y));
                    }
                    level.put(makeLightingInfo(srcLevel));
                }
                root.put(new CompoundTag("Level", level));
            }
            tags.put(y, new CompoundTag("", root));
        }
        // make sure the 0-15 range is there because it's using vanilla generator which expects it to be the case
        for (int y = 0; y < 16; y++) {
            if (!tags.containsKey(y)) {
                tags.put(y, emptyCube(x, y, z));
            }
        }
        return tags;
    }

    private CompoundTag emptyCube(int x, int y, int z) {
        CompoundMap root = new CompoundMap();
        {
            CompoundMap level = new CompoundMap();

            {
                level.put(new ByteTag("v", (byte) 1));
                level.put(new IntTag("x", x));
                level.put(new IntTag("y", y));
                level.put(new IntTag("z", z));

                level.put(new ByteTag("populated", true));
                level.put(new ByteTag("fullyPopulated", true));
                level.put(new ByteTag("isSurfaceTracked", true)); // it's empty, no need to re-track

                // no need for Sections, CC has isEmpty check for that

                level.put(new ByteTag("initLightDone", false));

                level.put(new ListTag<>("Entities", CompoundTag.class, emptyList()));
                level.put(new ListTag<>("TileEntities", CompoundTag.class, emptyList()));

                level.put(makeEmptyLightingInfo());
            }
            root.put(new CompoundTag("Level", level));
        }
        return new CompoundTag("", root);
    }

    private CompoundTag makeEmptyLightingInfo() {
        IntArrayTag heightmap = new IntArrayTag("LastHeightMap", new int[256]);
        CompoundMap lightingInfoMap = new CompoundMap();
        lightingInfoMap.put(heightmap);
        return new CompoundTag("LightingInfo", lightingInfoMap);
    }


    private CompoundTag fixSection(CompoundTag srcSection) {
        ByteArrayTag data = (ByteArrayTag) srcSection.getValue().get("Blocks");
        byte[] ids = data.getValue();
        // TODO: handle it the forge way
        for (int i = 0; i < ids.length; i++) {
            if (ids[i] == 7) { // bedrock
                ids[i] = 1; // stone
            }
        }
        return srcSection;
    }

    private CompoundTag makeLightingInfo(CompoundMap srcLevel) {
        IntArrayTag heightmap = new IntArrayTag("LastHeightMap", (int[]) srcLevel.get("HeightMap").getValue());
        CompoundMap lightingInfoMap = new CompoundMap();
        lightingInfoMap.put(heightmap);
        return new CompoundTag("LightingInfo", lightingInfoMap);
    }

    @SuppressWarnings("unchecked")
    private ListTag<CompoundTag> filterEntities(ListTag<CompoundTag> entities, int cubeY) {
        double yMin = cubeY * 16;
        double yMax = yMin + 16;
        List<CompoundTag> cubeEntities = new ArrayList<>();
        for (CompoundTag entityTag : entities.getValue()) {
            List<DoubleTag> pos = ((ListTag<DoubleTag>) entityTag.getValue().get("Pos")).getValue();
            double y = pos.get(1).getValue();
            if (y >= yMin && y < yMax) {
                cubeEntities.add(entityTag);
            }
        }
        return new ListTag<>(entities.getName(), CompoundTag.class, cubeEntities);
    }

    @SuppressWarnings("unchecked")
    private ListTag<?> filterTileEntities(ListTag<?> tileEntities, int cubeY) {
        // empty list is list of EndTags
        if (tileEntities.getValue().isEmpty()) {
            return tileEntities;
        }
        int yMin = cubeY * 16;
        int yMax = yMin + 16;
        List<CompoundTag> cubeTEs = new ArrayList<>();
        for (CompoundTag teTag : ((ListTag<CompoundTag>) tileEntities).getValue()) {
            int y = ((IntTag) teTag.getValue().get("y")).getValue();
            if (y >= yMin && y < yMax) {
                cubeTEs.add(teTag);
            }
        }
        return new ListTag<>(tileEntities.getName(), CompoundTag.class, cubeTEs);
    }

    private ListTag<CompoundTag> filterTileTicks(ListTag<CompoundTag> tileTicks, int cubeY) {
        int yMin = cubeY * 16;
        int yMax = yMin + 16;
        List<CompoundTag> cubeTicks = new ArrayList<>();
        for (CompoundTag tileTick : tileTicks.getValue()) {
            int y = ((IntTag) tileTick.getValue().get("y")).getValue();
            if (y >= yMin && y < yMax) {
                cubeTicks.add(tileTick);
            }
        }
        return new ListTag<>(tileTicks.getName(), CompoundTag.class, cubeTicks);
    }

}
