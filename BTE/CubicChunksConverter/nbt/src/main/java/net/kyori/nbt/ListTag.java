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

import org.checkerframework.checker.index.qual.NonNegative;
import org.checkerframework.checker.nullness.qual.NonNull;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;
import java.util.AbstractList;
import java.util.ArrayList;
import java.util.List;

import static java.util.Objects.requireNonNull;

/**
 * A list tag.
 */
public final class ListTag extends AbstractList<Tag> implements IndexedCollectionTag<Tag> {
  /**
   * The maximum depth.
   */
  public static final int MAX_DEPTH = 512;
  /**
   * The list of tags.
   */
  private final List<Tag> tags = new ArrayList<>();
  /**
   * The type of this list.
   */
  private @NonNull TagType type;

  public ListTag() {
    this(TagType.END);
  }

  public ListTag(final @NonNull TagType type) {
    this.type = type;
  }

  /**
   * Creates a list tag with some double values.
   *
   * @param values the double values
   * @return the list tag
   */
  public static ListTag doubles(final double... values) {
    final ListTag tag = new ListTag();
    for(final double value : values) {
      tag.add(new DoubleTag(value));
    }
    return tag;
  }

  /**
   * Creates a list tag with some float values.
   *
   * @param values the float values
   * @return the list tag
   */
  public static ListTag floats(final float... values) {
    final ListTag tag = new ListTag();
    for(final float value : values) {
      tag.add(new FloatTag(value));
    }
    return tag;
  }

  /**
   * Creates a list tag with some string values.
   *
   * @param values the string values
   * @return the list tag
   */
  public static ListTag strings(final String... values) {
    final ListTag tag = new ListTag();
    for(int i = 0, length = values.length; i < length; i++) {
      tag.add(new StringTag(requireNonNull(values[i], "value at index " + i)));
    }
    return tag;
  }

  /**
   * Gets the type of this list.
   *
   * @return the type
   */
  public @NonNull TagType listType() {
    return this.type;
  }

  /**
   * Gets a tag.
   *
   * @param index the index
   * @return the tag
   * @throws IndexOutOfBoundsException if the index is out of range
   */
  @Override
  public @NonNull Tag get(final @NonNegative int index) {
    return this.tags.get(index);
  }

  /**
   * Gets a byte.
   *
   * @param index the index
   * @return the byte value, or {@code 0}
   */
  public byte getByte(final @NonNegative int index) {
    return this.getByte(index, (byte) 0);
  }

  /**
   * Gets a byte.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the byte value, or {@code defaultValue}
   */
  public byte getByte(final @NonNegative int index, final byte defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type().number()) {
      return ((NumberTag) tag).byteValue();
    }
    return defaultValue;
  }

  /**
   * Gets a short.
   *
   * @param index the index
   * @return the short value, or {@code 0}
   */
  public short getShort(final @NonNegative int index) {
    return this.getShort(index, (short) 0);
  }

  /**
   * Gets a short.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the short value, or {@code defaultValue}
   */
  public short getShort(final @NonNegative int index, final short defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type().number()) {
      return ((NumberTag) tag).shortValue();
    }
    return defaultValue;
  }

  /**
   * Gets an int.
   *
   * @param index the index
   * @return the int value, or {@code 0}
   */
  public int getInt(final @NonNegative int index) {
    return this.getInt(index, 0);
  }

  /**
   * Gets an int.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the int value, or {@code defaultValue}
   */
  public int getInt(final @NonNegative int index, final int defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type().number()) {
      return ((NumberTag) tag).intValue();
    }
    return defaultValue;
  }

  /**
   * Gets a long.
   *
   * @param index the index
   * @return the long value, or {@code 0}
   */
  public long getLong(final @NonNegative int index) {
    return this.getLong(index, 0L);
  }

  /**
   * Gets a long.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the long value, or {@code defaultValue}
   */
  public long getLong(final @NonNegative int index, final long defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type().number()) {
      return ((NumberTag) tag).longValue();
    }
    return defaultValue;
  }

  /**
   * Gets a float.
   *
   * @param index the index
   * @return the float value, or {@code 0}
   */
  public float getFloat(final @NonNegative int index) {
    return this.getFloat(index, 0f);
  }

  /**
   * Gets a float.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the float value, or {@code defaultValue}
   */
  public float getFloat(final @NonNegative int index, final float defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type().number()) {
      return ((NumberTag) tag).floatValue();
    }
    return defaultValue;
  }

  /**
   * Gets a double.
   *
   * @param index the index
   * @return the double value, or {@code 0}
   */
  public double getDouble(final @NonNegative int index) {
    return this.getDouble(index, 0d);
  }

  /**
   * Gets a double.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the double value, or {@code defaultValue}
   */
  public double getDouble(final @NonNegative int index, final double defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type().number()) {
      return ((NumberTag) tag).doubleValue();
    }
    return defaultValue;
  }

  /**
   * Gets an array of bytes.
   *
   * @param index the index
   * @return the array of bytes, or a zero-length array
   */
  public @NonNull byte[] getByteArray(final @NonNegative int index) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.BYTE_ARRAY) {
      return ((ByteArrayTag) tag).value();
    }
    return new byte[0];
  }

  /**
   * Gets an array of bytes.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the array of bytes, or {@code defaultValue}
   */
  public @NonNull byte[] getByteArray(final @NonNegative int index, final @NonNull byte[] defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.BYTE_ARRAY) {
      return ((ByteArrayTag) tag).value();
    }
    return defaultValue;
  }

  /**
   * Gets a string.
   *
   * @param index the index
   * @return the string value, or {@code ""}
   */
  public @NonNull String getString(final @NonNegative int index) {
    return this.getString(index, "");
  }

  /**
   * Gets a string.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the string value, or {@code defaultValue}
   */
  public @NonNull String getString(final @NonNegative int index, final @NonNull String defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.STRING) {
      return ((StringTag) tag).value();
    }
    return defaultValue;
  }

  /**
   * Gets a compound.
   *
   * @param index the index
   * @return the compound, or a new compound
   */
  public @NonNull CompoundTag getCompound(final @NonNegative int index) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.COMPOUND) {
      return (CompoundTag) tag;
    }
    return new CompoundTag();
  }

  /**
   * Gets a compound.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the compound, or {@code defaultValue}
   */
  public @NonNull CompoundTag getCompound(final @NonNegative int index, final @NonNull CompoundTag defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.COMPOUND) {
      return (CompoundTag) tag;
    }
    return defaultValue;
  }

  /**
   * Gets an array of ints.
   *
   * @param index the index
   * @return the array of ints, or a zero-length array
   */
  public @NonNull int[] getIntArray(final @NonNegative int index) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.INT_ARRAY) {
      return ((IntArrayTag) tag).value();
    }
    return new int[0];
  }

  /**
   * Gets an array of ints.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the array of ints, or {@code defaultValue}
   */
  public @NonNull int[] getIntArray(final @NonNegative int index, final @NonNull int[] defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.INT_ARRAY) {
      return ((IntArrayTag) tag).value();
    }
    return defaultValue;
  }

  /**
   * Gets an array of longs.
   *
   * @param index the index
   * @return the array of longs, or a zero-length array
   */
  public @NonNull long[] getLongArray(final @NonNegative int index) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.LONG_ARRAY) {
      return ((LongArrayTag) tag).value();
    }
    return new long[0];
  }

  /**
   * Gets an array of longs.
   *
   * @param index the index
   * @param defaultValue the default value
   * @return the array of longs, or {@code defaultValue}
   */
  public @NonNull long[] getLongArray(final @NonNegative int index, final @NonNull long[] defaultValue) {
    final Tag tag = this.get(index);
    if(tag.type() == TagType.LONG_ARRAY) {
      return ((LongArrayTag) tag).value();
    }
    return defaultValue;
  }

  /**
   * Adds a tag.
   *
   * @param tag the tag
   */
  @Override
  public boolean add(final @NonNull Tag tag) {
    // don't allow an end tag to be added
    if(tag.type() == TagType.END) {
      throw new IllegalArgumentException(String.format("Cannot add a '%s' to a '%s'", EndTag.class.getSimpleName(), ListTag.class.getSimpleName()));
    }
    // set the type if it has not yet been set
    if(this.type == TagType.END) {
      this.type = tag.type();
    }
    this.tags.add(tag);
    return true;
  }

  /**
   * Sets the tag at the specified index.
   *
   * @param index the index
   * @param tag the tag
   * @throws IndexOutOfBoundsException if the index is out of range
   */
  @Override
  public Tag set(final int index, final @NonNull Tag tag) {
    // don't allow an end tag to be added
    if(tag.type() == TagType.END) {
      throw new IllegalArgumentException(String.format("Cannot add a '%s' to a '%s'", EndTag.class.getSimpleName(), ListTag.class.getSimpleName()));
    }
    // set the type if it has not yet been set
    if(this.type == TagType.END) {
      this.type = tag.type();
    }
    return this.tags.set(index, tag);
  }

  /**
   * Removes a tag.
   *
   * @param index the index
   * @return the tag
   * @throws IndexOutOfBoundsException if the index is out of range
   */
  @Override
  public @NonNull Tag remove(final int index) {
    return this.tags.remove(index);
  }

  @Override
  public int size() {
    return this.tags.size();
  }

  @Override
  public boolean isEmpty() {
    return this.tags.isEmpty();
  }

  @Override
  public void read(final TagTypeMap typeMap, final @NonNull DataInput input, final int depth) throws IOException {
    if(depth > MAX_DEPTH) {
      throw new IllegalStateException(String.format("Depth of %d is higher than max of %d", depth, MAX_DEPTH));
    }

    this.type = typeMap.fromId(input.readByte());

    final int length = input.readInt();
    for(int i = 0; i < length; i++) {
      final Tag tag = this.type.create();
      tag.read(typeMap, input, depth + 1);
      this.tags.add(tag);
    }
  }

  @Override
  public void write(final TagTypeMap typeMap, final @NonNull DataOutput output) throws IOException {
    output.writeByte(typeMap.getId(this.type));
    output.writeInt(this.tags.size());
    for(int i = 0, length = this.tags.size(); i < length; i++) {
      this.tags.get(i).write(typeMap, output);
    }
  }

  @Override
  public @NonNull TagType type() {
    return TagType.LIST;
  }

  @Override
  public @NonNull ListTag copy() {
    final ListTag copy = new ListTag(this.type);
    for(final Tag tag : this.tags) {
      copy.tags.add(tag.copy()); // add directly to list, we can skip sanity checks
    }
    return copy;
  }

  @Override
  public int hashCode() {
    return this.tags.hashCode();
  }

  @Override
  public boolean equals(final Object that) {
    return this == that || (that instanceof ListTag && this.tags.equals(((ListTag) that).tags));
  }
}
