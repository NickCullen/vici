

// Start of test
#define TEST(name) { \
	printf("Start of test %s\n", #name);	\
	VTimer timer;		\
	timer.Begin();		\

#define END() timer.Tick();		\
	printf("Finished in %fms\n", timer.GetTimeInMilliSeconds());	\
	}