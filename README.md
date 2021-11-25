# ESP GPS TimeZone

This is a library to determine the timezone for a given GPS coordinate. The
library uses the combined-with-oceans.json file found at [Timezone Boundary
Builder](https://github.com/evansiroky/timezone-boundary-builder). This file is
processed by the code in the GeoJson directory to produce the per timezone
files found in the SDCard/TimeZoneJson directory. All the timezone JSON files
total over 230 Megabytes and an SD card or other large storage is required for
all timezones, but a  subset of the files can be supported by the flash filesystem.

## Using the library

An ESPGPSTimeZone object is first created specifying the filesystem and the path
to the timezone JSON files. findTZ can then be called to lookup the timezone
for a given coordinate. If the lookup is successful the timezone name,
posix timezone specification, and radius are available. Radius can be used to
check if a new coordinate is in the same timezone without having to process
any timezone JSON files.

## Declaring the ESPGPSTimeZone object

```c++
ESPGPSTimeZone objectName(fs::FS& fileSys, const char* path);
```

- **fileSys** - the file system for the configFileName (LittleFS, SPIFFS, SD)
- **path** - the path to the timezone JSON files

## Object Methods

```c++
bool findTZ(double lat, double longi)
```

- **lat** - the latitude of the GPS coordinate
- **longi** - the longitude of the GPS coordinate

Find the timezone of the GPS coordinate, returning false if the timezone can
not be found

```c++
bool inCircle(double centerLat, double centerLong,
              double locationLat, double locationLong, double radius)
bool inCircle(std::array<double, 2> center, std::array<double, 2> location,
              double radius)
```

- **centerLat** - the latitude of the circle center GPS coordinate
- **centerLong** - the longitude of the circle center GPS coordinate
- **locationLat** - the latitude of the location GPS coordinate
- **locationLong** - the longitude of the location GPS coordinate
- **radius** - the radius of the circle
- **center** - the circle center GPS coordinate { longitude, latitude }
- **location** - the location GPS coordinate { longitude, latitude }

Determine if a given GPS coordinate is within a circle defined by the center
coordinate and the radius. This allows a GPS coordinate (center) and radius to
be stored and used to determine if a new location is in the same timezone
without having to process any timezone JSON files.

```c++
const char* tzName()
```

Get the timezone name.

```c++
const char* posix()
```

Get the timezone posix specification.

```c++
double radius()
```

Get radius of the current lookup. Then a coordinate is successfully looked up
the radius value is set so that any point inside the circle defined by the
coordinate and radius is guaranteed to be in the same timezone as the
coordinate.
