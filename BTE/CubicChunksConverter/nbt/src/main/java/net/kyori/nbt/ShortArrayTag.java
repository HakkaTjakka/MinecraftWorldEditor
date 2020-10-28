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

public class ShortArrayTag extends AbstractList<ShortTag> implements IndexedCollectionTag<ShortTag> {
  /**
   * The array of shorts.
   */
  private short[] value;

  ShortArrayTag() {
  }

  public ShortArrayTag(final short @NonNull [] value) {
    this.value = value;
  }

  @Override
  public int size() {
    return this.value.length;
  }

  @Override
  public ShortTag get(final int index) {
    return new ShortTag(this.value[index]);
  }

  /**
   * Gets the array of shorts.
   *
   * @return the array of shorts
   */
  public short @NonNull [] value() {
    return this.value;
  }

  @Override
  public void read(final TagTypeMap typeMap, final @NonNull DataInput input, final int depth) throws IOException {
    final int length = input.readInt();
    this.value = new short[length];
    for(int i = 0; i < length; i++) {
      this.value[i] = input.readShort();
    }
  }

  @Override
  public void write(final TagTypeMap typeMap, final @NonNull DataOutput output) throws IOException {
    output.writeInt(this.value.length);
    for(int i = 0, length = this.value.length; i < length; i++) {
      output.writeShort(this.value[i]);
    }
  }

  @Override
  public @NonNull TagType type() {
    return TagType.SHORT_ARRAY;
  }

  @Override
  public @NonNull ShortArrayTag copy() {
    final short[] value = new short[this.value.length];
    System.arraycopy(this.value, 0, value, 0, this.value.length);
    return new ShortArrayTag(value);
  }

  @Override
  public int hashCode() {
    return Arrays.hashCode(this.value);
  }

  @Override
  public boolean equals(final Object that) {
    return this == that || (that instanceof ShortArrayTag && Arrays.equals(this.value, ((ShortArrayTag) that).value));
  }
}
