#ifndef __UTILS__H_
#define __UTILS__H_

#if TESTING == 1
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

#endif /* __UTILS__H_ */
