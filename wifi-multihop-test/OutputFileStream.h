#ifndef OUTPUTFILE_H_
#define OUTPUTFILE_H_
#include <fstream>
namespace abe {

class OutputFileStream: public std::ofstream {
	std::string outputFileName;
public:
	OutputFileStream(const double, const int);
	virtual ~OutputFileStream();
};
}//abe

#endif /* OUTPUTFILE_H_ */
