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

/**
 * A tag representing a {@code byte}.
 */
public final class ByteTag implements NumberTag {
  /**
   * A {@code byte} representing a {@code boolean} value of {@code false}.
   */
  static final byte FALSE = 0;
  /**
   * A {@code byte} representing a {@code boolean} value of {@code true}.
   */
  static final byte TRUE = 1;
  /**
   * The byte value.
   */
  private byte value;

  ByteTag() {
  }

  public ByteTag(final byte value) {
    this.value = value;
  }

  @Override
  public byte byteValue() {
    return this.value;
  }

  @Override
  public double doubleValue() {
    return (double) this.value;
  }

  @Override
  public float floatValue() {
    return (float) this.value;
  }

  @Override
  public int intValue() {
    return (int) this.value;
  }

  @Override
  public long longValue() {
    return (long) this.value;
  }

  @Override
  public short shortValue() {
    return (short) this.value;
  }

  @Override
  public void read(final TagTypeMap typeMap, final @NonNull DataInput input, final int depth) throws IOException {
    this.value = input.readByte();
  }

  @Override
  public void write(final TagTypeMap typeMap, final @NonNull DataOutput output) throws IOException {
    output.writeByte(this.value);
  }

  @Override
  public @NonNull TagType type() {
    return TagType.BYTE;
  }

  @Override
  public @NonNull ByteTag copy() {
    return new ByteTag(this.value);
  }

  @Override
  public int hashCode() {
    return Byte.hashCode(this.value);
  }

  @Override
  public boolean equals(final Object that) {
    return this == that || (that instanceof ByteTag && this.value == ((ByteTag) that).value);
  }
}
