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
package cubicchunks.converter.lib.util;

import cubicchunks.converter.lib.convert.cc2ccrelocating.CC2CCRelocatingDataConverter;

import java.util.Objects;

import static java.lang.Math.max;
import static java.lang.Math.min;

public final class BoundingBox {
    private final Vector3i minPos;
    private final Vector3i maxPos;

    public BoundingBox(int minX, int minY, int minZ, int maxX, int maxY, int maxZ) {
        minPos = new Vector3i(min(minX, maxX), min(minY, maxY), min(minZ, maxZ));
        maxPos = new Vector3i(max(minX, maxX), max(minY, maxY), max(minZ, maxZ));
    }

    public BoundingBox(Vector3i minPos, Vector3i maxPos) {
        this(minPos.getX(), minPos.getY(), minPos.getZ(), maxPos.getX(), maxPos.getY(), maxPos.getZ());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        BoundingBox that = (BoundingBox) o;
        return minPos.getX() == that.minPos.getX() &&
                minPos.getY() == that.minPos.getY() &&
                minPos.getZ() == that.minPos.getZ() &&
                maxPos.getX() == that.maxPos.getX() &&
                maxPos.getY() == that.maxPos.getY() &&
                maxPos.getZ() == that.maxPos.getZ();
    }

    public BoundingBox asRegionCoords(Vector3i regionSize) {
        return new BoundingBox(
                Math.floorDiv(this.minPos.getX(), regionSize.getX()),
                Math.floorDiv(this.minPos.getY(), regionSize.getY()),
                Math.floorDiv(this.minPos.getZ(), regionSize.getZ()),
                Math.floorDiv(this.maxPos.getX(), regionSize.getX()),
                Math.floorDiv(this.maxPos.getY(), regionSize.getY()),
                Math.floorDiv(this.maxPos.getZ(), regionSize.getZ())
        );
    }

    public BoundingBox add(Vector3i vector3i) {
        return new BoundingBox(minPos.add(vector3i), maxPos.add(vector3i));
    }

    @Override
    public int hashCode() {
        return Objects.hash(minPos.getX(), minPos.getY(), minPos.getZ(), maxPos.getX(), maxPos.getY(), maxPos.getZ());
    }

    public boolean intersects(int x, int y, int z) {
        return x >= minPos.getX() && x <= maxPos.getX() &&
                y >= minPos.getY() && y <= maxPos.getY() &&
                z >= minPos.getZ() && z <= maxPos.getZ();
    }

    public boolean columnIntersects(int x, int z) {
        return x >= minPos.getX() && x <= maxPos.getX() &&
                z >= minPos.getZ() && z <= maxPos.getZ();
    }

    public Vector3i getMinPos() {
        return minPos;
    }
    public Vector3i getMaxPos() {
        return maxPos;
    }

    @Override
    public String toString() {
        return "BoundingBox{" +
                "minPos=" + minPos +
                ", maxPos=" + maxPos +
                '}';
    }
}
