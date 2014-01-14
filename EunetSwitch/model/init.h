#ifndef INIT_H_
#define INIT_H_

#define DECLARE_DIDDNCC private: bool isNotifyConstructionCompletedCalled; bool isDoInitializeCalled;	bool isDoDisposeCalled;protected:	virtual void DoInitialize();	virtual void NotifyConstructionCompleted();	virtual void DoDispose();
#define INIT_DIDDNCC_FLAGS isNotifyConstructionCompletedCalled(false),isDoInitializeCalled(false), isDoDisposeCalled(false)
#define ASSERT_DI 	NS_ASSERT(!this->isDoInitializeCalled); this->isDoInitializeCalled = true;
#define ASSERT_DD    NS_ASSERT(!this-isDoDisposeCalled);	this->isDoDisposeCalled = true; 	NS_ASSERT(this->isNotifyConstructionCompletedCalled);
#define ASSERT_NCC   NS_ASSERT(!this->isNotifyConstructionCompletedCalled);	this->isNotifyConstructionCompletedCalled = true;

#endif /* INIT_H_ */
