#pragma once

namespace MEMORYSIZES {
    // Gameboy Memory Sizes:
    // (Byte), 8KiB VRAM + 8KiB Work Ram + 160B OAM + 128B I/O + 127B High RAM + 1B Interrupt Register
    const static int DMG_RAM_SIZE = 16'800;
    // (Byte), How much cartridge RAM we can support (64kB and 128kB are possible for a cartridge, but not supported).
    const static int MAX_CARTRIDGE_RAM = 32'768;
    // The maximum size of the addressable addressspace in the Gameboy.
    const static int ADDRESS_SPACE_SIZE = 65'536;

    // Map-RAM:
    // map-size = <=500x500 = 250.000_10 >= 65.536_10 = 2^16
    const static int BYTES_PER_EVENT_POS = 2;
    // 8400 Events needed.
    const static int NUM_DMG_RAM_EVENTS = DMG_RAM_SIZE / BYTES_PER_EVENT_POS;



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
    // TODO: I should change the following variables: 
        // TODO: LABELS_PER_EPAGE: [1, RPGMAKER::MAX_LABELS_PER_EPAGE]. This will make MAX_LABELS_PER_EPAGE unecessary. With this variable I can set how many labels I want to have. Less Labels means less code. Halfing this from n to n/2: O(log(n)) => O(log(n/2))
        // TODO: VARS_PER_LABEL: [2, ...]. This would allow a single Label to have multiple variables. Right now we always have two variables per Label. Increasing this will increase the amount of static variables for reading, but drastically reduce the number of labels I need in all pages. This could be a good tradeoff to increase the performance. Because having something like 10 extra static variables that can read 10*BYTES_PER_VAR at once. But it is currently unclear how much time writing to these static variables takes compared to the jump. But just doubling the number of variables per E-Page from 2 to 4, will half the amount of Labels you need per EPage for the same amount of Memory you can address in a single event page. And this halves the total amount of generated code!
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
    // How many commands the map rom header has.
    const static int MAP_ROM_HEADER_COUNT = 4;
    // How many commands the map rom label has.
    const static int MAP_ROM_LABEL_COUNT = 10;


    // CHARA-RAM:
    // Number of items per type (used as data).
    const static int NUM_OF_WEAPONS = 2048;
    const static int NUM_OF_SHIELDS = 2048;
    const static int NUM_OF_BODY = 2048;
    const static int NUM_OF_HEAD = 2048;
    const static int NUM_OF_ACCESSORY = 1024;
    const static int TOTAL_USED_ITEMS = NUM_OF_WEAPONS + NUM_OF_SHIELDS + NUM_OF_BODY + NUM_OF_HEAD + NUM_OF_ACCESSORY;
    const static int MAX_NUM_ITEMS = 10000;
    // How many Bytes can be represented with the Exp of one character.
    const static int BYTES_PER_EXP = 2;
    // How many Bytes a single character can store.
    const static int BYTES_PER_CHAR = 13;

    static_assert(TOTAL_USED_ITEMS <= MAX_NUM_ITEMS);
};