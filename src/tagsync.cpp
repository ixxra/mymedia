#include <iostream>
//#include <future>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <json/value.h>
#include <json/writer.h>

static const Json::StaticString LOCATION("location");
static const Json::StaticString TITLE("title");
static const Json::StaticString ARTIST("artist");
static const Json::StaticString ALBUM("album");
static const Json::StaticString TRACK("track");
static const Json::StaticString YEAR("year");

void parseAndWrite(const char* location, Json::StreamWriter* const writer)
{
  Json::Value metadata;
  metadata[LOCATION] = location;
  TagLib::FileRef f(location);
  TagLib::Tag* tag = f.tag();
  TagLib::String artist = tag->artist();
  TagLib::String album = tag->artist();
  TagLib::String title = tag->title();

  uint track = tag->track();
  uint year = tag->year();

  metadata[TITLE] = title.toCString(true);
  metadata[ARTIST] = artist.toCString(true);
  metadata[ALBUM] = album.toCString(true);
  metadata[TRACK] = track;
  metadata[YEAR] = year;

  writer->write(metadata, &std::cout);

}

int main(int argc, const char** argv)
{
  Json::StreamWriterBuilder factory;
  //std::unique_ptr<Json::StreamWriter> const writer(factory.newStreamWriter());
  Json::StreamWriter* const writer(factory.newStreamWriter());

  std::cout << "[";
  for (int i=1; i<argc-1; i++){
    parseAndWrite(argv[i], writer);
    std::cout << "," << std::endl;
  }
  if (argc > 1){
    parseAndWrite(argv[argc - 1], writer);
  }
  std::cout << "]" << std::endl;

  return 0;
}
