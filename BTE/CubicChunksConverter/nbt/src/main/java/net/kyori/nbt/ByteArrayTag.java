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
 * A tag representing an array of {@code byte}s.
 */
public final class ByteArrayTag extends AbstractList<ByteTag> implements IndexedCollectionTag<ByteTag> {
  /**
   * The array of bytes.
   */
  private byte[] value;

  ByteArrayTag() {
  }

  public ByteArrayTag(final byte@NonNull[] value) {
    this.value = value;
  }

  @Override
  public int size() {
    return this.value.length;
  }

  @Override
  public ByteTag get(final int index) {
    return new ByteTag(this.value[index]);
  }

  /**
   * Gets the array of bytes.
   *
   * @return the array of bytes
   */
  public byte@NonNull[] value() {
    return this.value;
  }

  @Override
  public void read(final TagTypeMap typeMap, final @NonNull DataInput input, final int depth) throws IOException {
    final int length = input.readInt();
    this.value = new byte[length];
    input.readFully(this.value);
  }

  @Override
  public void write(final TagTypeMap typeMap, final @NonNull DataOutput output) throws IOException {
    output.writeInt(this.value.length);
    output.write(this.value);
  }

  @Override
  public @NonNull TagType type() {
    return TagType.BYTE_ARRAY;
  }

  @Override
  public @NonNull ByteArrayTag copy() {
    final byte[] value = new byte[this.value.length];
    System.arraycopy(this.value, 0, value, 0, this.value.length);
    return new ByteArrayTag(value);
  }

  @Override
  public int hashCode() {
    return Arrays.hashCode(this.value);
  }

  @Override
  public boolean equals(final Object that) {
    return this == that || (that instanceof ByteArrayTag && Arrays.equals(this.value, ((ByteArrayTag) that).value));
  }
}
