#include <stdio.h>
#include <string.h>
 #include <libusb-1.0/libusb.h>

 int main()
 {
         int res, i, ret;
         char buf[256];
         struct libusb_device **devs;
         struct libusb_device *dev;
         struct libusb_device_handle *devh;
         struct libusb_device_descriptor descr;
         struct libusb_config_descriptor *cdescr;

         libusb_init(NULL);
         devh = libusb_open_device_with_vid_pid(NULL, 0x03f0, 0x1f4a); // MS mouse VID/PID
         dev = libusb_get_device(devh);
         if (dev < 0){
             printf("Failed to get the device ");
             return -1;
         }
         ret = libusb_get_config_descriptor(NULL, devh, cdescr);
         if (ret < 0){
         printf("Failed to get config descriptor");
         return -1;
         }
         /*if (cdescr->extra_length){
         printf("");
         }*/
         res = libusb_detach_kernel_driver(devh, 0);
         printf("Res: %d\n", res);
         
         res = libusb_claim_interface(devh, 0);
         if (res < 0){
             printf("Failed to get the device ");
             return -1;
         }
         printf("Res: %d\n", res);

         memset(buf, 0, sizeof(buf));
         res = libusb_get_descriptor(devh, LIBUSB_DT_REPORT, 0, buf, sizeof(buf));
         printf("Res: %d\n", res);
         printf("BUS: %s", buf);
         return 0;
}
