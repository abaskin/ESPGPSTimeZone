# Generate the TimeZone JSON Files

This uses the combined-with-oceans.json file found at [Timezone Boundary
Builder](https://github.com/evansiroky/timezone-boundary-builder). The file is
processed by the code to produce the per timezone files found in the
SDCard/TimeZoneJson directory. All the timezone JSON files total over 230
Megabytes and an SD card or other large storage is required for all, but a
subset of the files can be supported by the flash filesystem. The code uses
the native platform in PlatformIO and may need to be adjusted depending on the
OS used. `boost::replace_all_copy` is used and will need to be installed.
