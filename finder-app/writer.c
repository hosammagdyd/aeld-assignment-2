#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
  setlogmask(LOG_UPTO(LOG_DEBUG));

  if (argc != 3) {
    syslog(LOG_ERR,
           "Invalid number of arguments: %d (expected 2: writefile writestr)",
           argc - 1);
    fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
    closelog();
    return 1;
  }

  const char *writefile = argv[1];
  const char *writestr = argv[2];

  int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    syslog(LOG_ERR, "Could not open %s for writing: %s", writefile,
           strerror(errno));
    fprintf(stderr, "Error opening %s: %s\n", writefile, strerror(errno));
    closelog();
    return 1;
  }

  size_t towrite = strlen(writestr);
  ssize_t written = write(fd, writestr, towrite);

  if (written == -1) {
    syslog(LOG_ERR, "Write to %s failed: %s", writefile, strerror(errno));
    fprintf(stderr, "Error writing to %s: %s\n", writefile, strerror(errno));
    close(fd);
    closelog();
    return 1;
  }

  if ((size_t)written != towrite) {
    syslog(LOG_ERR, "Short write to %s: wrote %zd of %zu bytes", writefile,
           written, towrite);
    fprintf(stderr, "Short write to %s: wrote %zd of %zu bytes\n", writefile,
            written, towrite);
    close(fd);
    closelog();
    return 1;
  }

  if (close(fd) == -1) {
    syslog(LOG_ERR, "Error closing %s: %s", writefile, strerror(errno));
    fprintf(stderr, "Error closing %s: %s\n", writefile, strerror(errno));
    closelog();
    return 1;
  }

  syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

  closelog();
  return 0;
}
