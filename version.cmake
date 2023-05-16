# Check if the VERSION_UPDATE variable is set to "1"
if (DEFINED VERSION_UPDATE AND "${VERSION_UPDATE}" STREQUAL "1")
    # Read the current version from a file
    file(READ "/home/bleppe/Documents/Programas/LCDTest/version.txt" VERSION_FILE_CONTENTS)

    # Split the version string into parts
    string(REPLACE "." ";" VERSION_PARTS "${VERSION_FILE_CONTENTS}")

    # Increment the last version part
    list(GET VERSION_PARTS -1 LAST_PART)
    math(EXPR INCREMENTED_LAST_PART "${LAST_PART} + 1")

    # Update the last part of the version
    list(REMOVE_AT VERSION_PARTS -1)
    list(APPEND VERSION_PARTS "${INCREMENTED_LAST_PART}")

    # Join the version parts into a string
    string(REPLACE ";" "." UPDATED_VERSION "${VERSION_PARTS}")

    # Write the updated version to the version file
    file(WRITE "/home/bleppe/Documents/Programas/LCDTest/version.txt" "${UPDATED_VERSION}")

    # Write the version macro to a header file
    file(WRITE "/home/bleppe/Documents/Programas/LCDTest/version.h" "#define VERSION \"${UPDATED_VERSION}\"")
else()
    # Copy the version file to the build directory without modification
    configure_file("/home/bleppe/Documents/Programas/LCDTest/version.txt" "/home/bleppe/Documents/Programas/LCDTest/version.txt" COPYONLY)
endif()
