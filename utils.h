#ifndef __UTILS__H_
#define __UTILS__H_

#if TESTING == 1
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

#endif /* __UTILS__H_ */
