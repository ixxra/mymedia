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

bool parseAndWrite(const char* location, Json::Writer& writer)
{
  Json::Value metadata;
  metadata[LOCATION] = location;
  TagLib::FileRef f(location);

  if (f.isNull()){
    return false;
  }

  if (f.tag() && !f.tag()->isEmpty()){
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
  }

  std::cout << writer.write(metadata);
  return true;
}

int main(int argc, const char** argv)
{
  //Json::StreamWriterBuilder factory;
  //std::unique_ptr<Json::StreamWriter> const writer(factory.newStreamWriter());
  //Json::StreamWriter* const writer(factory.newStreamWriter());
  Json::FastWriter writer;

  //std::cout << "[";
  for (int i=1; i<argc-1; i++){
    parseAndWrite(argv[i], writer);
    //std::cout << "," << std::endl;
  }
  if (argc > 1){
    parseAndWrite(argv[argc - 1], writer);
  }
  //std::cout << "]" << std::endl;

  return 0;
}
