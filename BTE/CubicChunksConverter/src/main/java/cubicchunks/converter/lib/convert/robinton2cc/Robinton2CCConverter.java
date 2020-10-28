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
package cubicchunks.converter.lib.convert.robinton2cc;

import cubicchunks.converter.lib.convert.ChunkDataConverter;
import cubicchunks.converter.lib.convert.data.CubicChunksColumnData;
import cubicchunks.converter.lib.convert.data.RobintonColumnData;
import net.kyori.nbt.ByteArrayTag;
import net.kyori.nbt.CompoundTag;
import net.kyori.nbt.IntArrayTag;
import net.kyori.nbt.ListTag;
import net.kyori.nbt.TagIO;
import net.kyori.nbt.TagTypeMaps;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UncheckedIOException;
import java.nio.ByteBuffer;
import java.util.*;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;
import java.util.zip.InflaterInputStream;

public class Robinton2CCConverter implements ChunkDataConverter<RobintonColumnData, CubicChunksColumnData> {

    @Override public Set<CubicChunksColumnData> convert(RobintonColumnData input) {
        try {
            Map<Integer, ByteBuffer> newData = new HashMap<>();
            for (int y : input.getCubeData().keySet()) {
                ByteBuffer buf = input.getCubeData().get(y);
                if (buf == RobintonSaveSection.EMPTY_BUFFER) {
                    newData.put(y, makeEmpty(input.getPosition().getEntryX(), y, input.getPosition().getEntryZ()));
                }
                CompoundTag tag = readCompressed(buf);

                CompoundTag oldLevel = tag.getCompound("Level");
                CompoundTag newLevel = convertCube(input, oldLevel, y);

                CompoundTag newTag = new CompoundTag();
                newTag.put("Level", newLevel);

                newData.put(y, writeCompressed(newTag));
            }

            return Collections.singleton( new CubicChunksColumnData(input.getDimension(), input.getPosition(), null, newData));
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    }

    private ByteBuffer makeEmpty(int x, int y, int z) throws IOException {
        CompoundTag level = new CompoundTag();

        level.putInt("v", 1);
        level.putInt("x", x);
        level.putInt("y", y);
        level.putInt("z", z);
        // some old worlds don't appear to have this flag, and populating those chunks again causes weird effects
        level.putBoolean("populated", true);
        level.putBoolean("fullyPopulated", true);
        level.putBoolean("initLightDone", true);
        level.putBoolean("isSurfaceTracked", true);

        level.put("LightingInfo", makeLightingInfo());


        CompoundTag root = new CompoundTag();
        root.put("Level", level);

        return writeCompressed(root);
    }

    private CompoundTag convertCube(RobintonColumnData input, CompoundTag oldLevel, int y) {
        CompoundTag newLevel = new CompoundTag();
        /*
         * Robinton's NBT:
         * ROOT
         * |- Level
         *  |- Data
         *  |- Entities
         *  |- yPos
         *  |- TileEntities
         *  |- TerrainPopulated
         *  |- SkyLight
         *  |- BlockLight
         *  |- Blocks
         *
         * New CC NBT:
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
        int oldY = oldLevel.getInt("yPos");
        if (oldY != y) {
            System.out.println("Stored Y coordinate " + oldY + " doesn't match region derived cube NBT position " +
                    y + ", Using region-derived position");
        }
        newLevel.putInt("v", 1);
        newLevel.putInt("x", input.getPosition().getEntryX());
        newLevel.putInt("y", y);
        newLevel.putInt("z", input.getPosition().getEntryZ());
        // some old worlds don't appear to have this flag, and populating those chunks again causes weird effects
        newLevel.putBoolean("populated", !oldLevel.contains("TerrainPopulated") || oldLevel.getBoolean("TerrainPopulated"));
        newLevel.putBoolean("fullyPopulated", true);
        newLevel.putBoolean("initLightDone", true);
        newLevel.putBoolean("isSurfaceTracked", false);

        CompoundTag section = new CompoundTag();
        {
            section.put("Blocks", flipXYFull(oldLevel.getByteArray("Blocks")));
            section.put("Data", flipXYNibble(oldLevel.getByteArray("Data")));
            section.put("BlockLight", flipXYNibble(oldLevel.getByteArray("BlockLight")));
            section.put("SkyLight", flipXYNibble(oldLevel.getByteArray("SkyLight")));
        }
        ListTag sections = new ListTag();
        sections.add(section);

        newLevel.put("Sections", sections);
        newLevel.put("TileEntities", oldLevel.getList("TileEntities"));
        newLevel.put("Entities", oldLevel.getList("Entities"));
        newLevel.put("LightingInfo", makeLightingInfo());
        return newLevel;
    }

    private ByteArrayTag flipXYFull(byte[] dataIn) {
        byte[] newData = new byte[4096];
        for (int i = 0; i < 4096; i++) {
            int x = i & 15;
            int y = i >> 8 & 15;
            int z = i >> 4 & 15;
            // current: yyyy zzzz xxxx
            // old:     xxxx zzzz yyyy
            int oldIdx = y | z << 4 | x << 8;
            newData[i] = dataIn[oldIdx];
        }
        return new ByteArrayTag(newData);
    }

    private ByteArrayTag flipXYNibble(byte[] dataIn) {
        byte[] newData = new byte[2048];
        for (int newIdx = 0; newIdx < 4096; newIdx++) {
            int x = newIdx & 15;
            int y = newIdx >> 8 & 15;
            int z = newIdx >> 4 & 15;
            // current: yyyy zzzz xxxx
            // old:     xxxx zzzz yyyy
            int oldIdx = y | z << 4 | x << 8;

            int oldNibbleIdx = oldIdx >>> 1;
            int nibbleIdx = newIdx >>> 1;

            boolean oldLower = (oldIdx & 1) == 0;
            boolean newLower = (newIdx & 1) == 0;

            int data = (dataIn[oldNibbleIdx] >>> (oldLower ? 0 : 4)) & 0xF;
            newData[nibbleIdx] |= data << (newLower ? 0 : 4);
        }
        return new ByteArrayTag(newData);
    }

    private CompoundTag makeLightingInfo() {
        int[] arr = new int[256];
        Arrays.fill(arr, Integer.MIN_VALUE / 2);
        IntArrayTag heightmap = new IntArrayTag(arr);
        CompoundTag lightingInfoMap = new CompoundTag();
        lightingInfoMap.put("LastHeightMap", heightmap);
        return lightingInfoMap;
    }


    public static CompoundTag readCompressed(ByteBuffer buf) throws IOException {
        InputStream is = new ByteArrayInputStream(buf.array());
        int i = is.read();
        BufferedInputStream data;
        if (i == 1) {
            data = new BufferedInputStream(new GZIPInputStream(is));
        } else if (i == 2) {
            data = new BufferedInputStream(new InflaterInputStream(is));
        } else {
            throw new UnsupportedOperationException();
        }

        return TagIO.readInputStream(TagTypeMaps.ROBINTON, data);
    }

    private static ByteBuffer writeCompressed(CompoundTag tag) throws IOException {
        ByteArrayOutputStream bytes = new ByteArrayOutputStream(4096);
        OutputStream nbtOut = new BufferedOutputStream(new GZIPOutputStream(bytes, 4096), 4096);
        TagIO.writeOutputStream(TagTypeMaps.ROBINTON, tag, nbtOut);
        nbtOut.close();
        bytes.flush();
        return ByteBuffer.wrap(bytes.toByteArray());
    }

}
