/*
 * This file is part of nbt, licensed under the MIT License.
 *
 * Copyright (c) 2017 KyoriPowered
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
package net.kyori.nbt;

import org.checkerframework.checker.nullness.qual.NonNull;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;
import java.util.AbstractList;
import java.util.Arrays;

/**
 * A tag representing an array of {@code long}s.
 */
public final class LongArrayTag extends AbstractList<LongTag> implements IndexedCollectionTag<LongTag> {
  /**
   * The array of longs.
   */
  private long[] value;

  LongArrayTag() {
  }

  public LongArrayTag(final long@NonNull[] value) {
    this.value = value;
  }

  @Override
  public int size() {
    return this.value.length;
  }

  @Override
  public LongTag get(final int index) {
    return new LongTag(this.value[index]);
  }

  /**
   * Gets the array of longs.
   *
   * @return the array of longs
   */
  public long@NonNull[] value() {
    return this.value;
  }

  @Override
  public void read(final TagTypeMap typeMap, final @NonNull DataInput input, final int depth) throws IOException {
    final int length = input.readInt();
    this.value = new long[length];
    for(int i = 0; i < length; i++) {
      this.value[i] = input.readLong();
    }
  }

  @Override
  public void write(final TagTypeMap typeMap, final @NonNull DataOutput output) throws IOException {
    output.writeInt(this.value.length);
    for(int i = 0, length = this.value.length; i < length; i++) {
      output.writeLong(this.value[i]);
    }
  }

  @Override
  public @NonNull TagType type() {
    return TagType.LONG_ARRAY;
  }

  @Override
  public @NonNull LongArrayTag copy() {
    final long[] value = new long[this.value.length];
    System.arraycopy(this.value, 0, value, 0, this.value.length);
    return new LongArrayTag(value);
  }

  @Override
  public int hashCode() {
    return Arrays.hashCode(this.value);
  }

  @Override
  public boolean equals(final Object that) {
    return this == that || (that instanceof LongArrayTag && Arrays.equals(this.value, ((LongArrayTag) that).value));
  }
}
