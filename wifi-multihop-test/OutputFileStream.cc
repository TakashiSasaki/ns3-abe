#include "OutputFileStream.h"

abe::OutputFileStream::OutputFileStream(const double lambda,
		const int sim_count) {
	//出力用ファイルの作成
	time_t now = time(NULL);
	struct tm *pnow = localtime(&now);
	char filename[256];
	sprintf(filename, "sim_out_%d_%d_%d%d%d%d%d%d.txt",
			static_cast<int> (lambda), sim_count, pnow->tm_year + 1900,
			pnow->tm_mon + 1, pnow->tm_mday, pnow->tm_hour, pnow->tm_min,
			pnow->tm_sec);
	this->outputFileName = filename;
	this->open(filename);
}// a constructor

abe::OutputFileStream::~OutputFileStream() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}// the destructor
