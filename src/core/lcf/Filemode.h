#pragma once

enum FILE_MODE {
    // Changes to the data structure will not be reflected on the file it was created from. Any changes to the data will not persist after restart.
    IN_MEMORY,
    // Changes to the data structure will persist as the data file is updated with the changes.
    SYNC_WITH_FILE
};