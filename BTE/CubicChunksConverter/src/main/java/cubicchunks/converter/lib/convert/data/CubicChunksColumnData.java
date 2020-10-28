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
package cubicchunks.converter.lib.convert.data;

import cubicchunks.converter.lib.Dimension;
import cubicchunks.regionlib.impl.EntryLocation2D;

import java.nio.ByteBuffer;
import java.util.Map;
import java.util.Objects;

public class CubicChunksColumnData {

    private final Dimension dimension;
    private final EntryLocation2D position;
    private final ByteBuffer columnData;
    private final Map<Integer, ByteBuffer> cubeData;

    public CubicChunksColumnData(Dimension dimension, EntryLocation2D position, ByteBuffer columnData,
        Map<Integer, ByteBuffer> cubeData) {
        this.dimension = dimension;
        this.position = position;
        this.columnData = columnData;
        this.cubeData = cubeData;
    }

    public Dimension getDimension() {
        return dimension;
    }

    public EntryLocation2D getPosition() {
        return position;
    }

    public ByteBuffer getColumnData() {
        return columnData;
    }

    public Map<Integer, ByteBuffer> getCubeData() {
        return cubeData;
    }

    @Override public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        CubicChunksColumnData that = (CubicChunksColumnData) o;
        return dimension.equals(that.dimension) &&
            position.equals(that.position) &&
            Objects.equals(columnData, that.columnData) &&
            cubeData.equals(that.cubeData);
    }

    @Override public int hashCode() {
        return Objects.hash(dimension, position, columnData, cubeData);
    }

    @Override public String toString() {
        return "CubicChunksColumnData{" +
            "dimension='" + dimension + '\'' +
            ", position=" + position +
            ", columnData=" + columnData +
            ", cubeData=" + cubeData +
            '}';
    }
}
