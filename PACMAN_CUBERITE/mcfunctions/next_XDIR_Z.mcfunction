setblock ~ ~ ~ air 0
setblock ~16 ~0 ~0 air 0
fill ~16 ~0 ~0 ~16 ~0 ~0 repeating_command_block 0 keep {Command:"/function abc:letter_XDIR_Z",auto:1b}
fill ~32 ~0 ~0 ~32 ~0 ~0 repeating_command_block 0 keep {Command:"/function abc:next_YDIR_B",auto:1b}
