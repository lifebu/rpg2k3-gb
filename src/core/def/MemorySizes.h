#pragma once

namespace MEMORYSIZES {
    // Gameboy Memory Sizes:
    // (Byte), 8KiB VRAM + 8KiB Work Ram + 160B OAM + 128B I/O + 127B High RAM + 1B Interrupt Register
    const static int DMG_RAM_SIZE = 16800;
    // (Byte), How much cartridge RAM we can support (64kB and 128kB are possible for a cartridge, but not supported).
    const static int MAX_CARTRIDGE_RAM = 32768;

    // Map-RAM:
    // map-size = 500x500 = 250000_10 >= 131072_10 = 2^17
    const static int BITS_PER_EVENT_POS = 17;
    // 7906 Events needed.
    const static int NUM_DMG_RAM_EVENTS = (DMG_RAM_SIZE * 8) / BITS_PER_EVENT_POS + 1;


    // Map-ROM:
    // TODO: which BYTES_PER_VAR values is best?
    // TODO: As a workaround for the large memory usage and large .xml files, BYTES_PER_VAR should be set to 3. This reduces the amount of generated code  for the map ROM drastically (which is the vast majority of the memory usage).
    // BYTES_PER_VAR € [1,3], because:
    // Var € [-9.999.999, 9.999.999] = 20Mio_10 >= 16.777.216_10 = 2^24 = 3 Bytes
    const static int BYTES_PER_VAR = 3;
    static_assert(1 <= BYTES_PER_VAR && BYTES_PER_VAR <= 3, 
    "BYTES_PER_VAR needs to be in Range [1, 3]");
    // GB Ops Read/Write [1,2] Bytes. 
    // If address falls onto last byte of one Var, I need the next Var. 
    // Therefore always return 2 Vars (6 Byte).
    const static int VARS_PER_READWRITE = 2;
    // Maximum number of labels possible per event page.
    const static int MAX_LABELS_PER_EPAGE = 1000; 
    // TODO: need to test which VARS_PER_EPAGE gives best performance! 
    // How many Variables one event page is responsible for. Range: [1, MAX_LABELS_PER_EPAGE].
    // Increasing this makes event-page code more complex, requires less event-pages in total.
    // Decreaing this makes event-pages code simpler, but we require more event-pages in total.
    const static int VARS_PER_EPAGE = 1000;
    static_assert(1 <= VARS_PER_EPAGE && VARS_PER_EPAGE <= MAX_LABELS_PER_EPAGE, 
    "VARS_PER_EPAGE needs to be in Range [VARS_PER_READWRITE, MAX_LABELS_PER_EPAGE]");
    // How many Bytes one event-page is responsible for. This is needed for converting Gameboy Addresses to EventIDs and Per Event-Page ByteOffsets.
    const static int BYTES_PER_EPAGE = VARS_PER_EPAGE * BYTES_PER_VAR;


    // CHARA-RAM:
    // Number of items per type (used as data).
    const static int NUM_OF_WEAPONS = 2048;
    const static int NUM_OF_SHIELDS = 2048;
    const static int NUM_OF_BODY = 2048;
    const static int NUM_OF_HEAD = 2048;
    const static int NUM_OF_ACCESSORY = 1024;
    const static int TOTAL_USED_ITEMS = NUM_OF_WEAPONS + NUM_OF_SHIELDS + NUM_OF_BODY + NUM_OF_HEAD + NUM_OF_ACCESSORY;
    const static int MAX_NUM_ITEMS = 10000;

    static_assert(TOTAL_USED_ITEMS <= MAX_NUM_ITEMS);
};