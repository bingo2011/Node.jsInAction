/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#ifndef WavReader_h
#define WavReader_h

#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

#include "WavDescriptor.h"
#include "rlog/StdioNode.h"
#include "rlog/RLogChannel.h"

bool hasExtension(const std::string& text, const std::string& substring);

class WavReader {
public:
   WavReader(const std::string& source, const std::string& dest);
   virtual ~WavReader();
   void open(const std::string& name, bool trace);
   void list(
         const boost::filesystem::path& dir, 
         const std::string &filename, 
         std::vector<boost::filesystem::path>& found) const;
   void listAll() const;
   void publishSnippets();
public:
   void writeSamples(std::ostream* out, char* data, 
         uint32_t startingSample, 
         uint32_t samplesToWrite, 
         uint32_t bytesPerSample,
         uint32_t channels=1);

private:
   rlog::StdioNode log{STDERR_FILENO};
   WavDescriptor* descriptor_;

   void seekToEndOfHeader(std::ifstream& file, int headerLength);
   std::string toString(int8_t* c, unsigned int size);

   rlog::RLogChannel* channel;

   std::string source_;
   std::string dest_;
};

#endif  
