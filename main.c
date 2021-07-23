#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

struct rtc_time {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};

#define RTC_RD_TIME   _IOR('p', 0x09, struct rtc_time) /* Read RTC time   */
#define RTC_SET_TIME  _IOW('p', 0x0a, struct rtc_time) /* Set RTC time    */

static char *rtc_file = "/dev/rtc0";

int main()
{
  int rtc_f = 0;
  int ret = 0;
  struct rtc_time rtc_data;

  rtc_f = open(rtc_file, O_RDONLY);
  if(rtc_f == -1) {
    printf("RTC %s open error\n", rtc_file);
    return 0;
  }
  ret = ioctl(rtc_f, RTC_RD_TIME, &rtc_data);
  if(ret == -1) {
    printf("RTC %s set time error\n", rtc_file);
    close(rtc_f);
    return 0;
  }

  printf("%02d/%02d/%04d/%02d:%02d:%02d - %d - %d - %d\n", rtc_data.tm_mday, rtc_data.tm_mon, rtc_data.tm_year + 1900, 
                                                           rtc_data.tm_hour, rtc_data.tm_min, rtc_data.tm_sec,
                                                           rtc_data.tm_wday, rtc_data.tm_yday, rtc_data.tm_isdst);

  close(rtc_f);

  return 0;
}