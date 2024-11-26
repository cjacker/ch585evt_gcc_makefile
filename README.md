# ch584/ch585 riscv usb/nfc/ble evt with gcc and makefile support

This is pre-converted ch585 riscv usb/nfc/ble evt firmware library with gcc and makefile support from WCH official CH585EVT.ZIP.

It is converted by [ch5xx_riscv_ble_evt_makefile_gcc_project_template](https://github.com/cjacker/ch5xx_riscv_ble_evt_makefile_gcc_project_template)

This firmware library support below parts from WCH:

- ch584
- ch585

The default part is set to 'ch585', you can change it with `./setpart.sh <part>`. the corresponding 'Link.ld' will update automatically from the template.

The default 'User' codes is not BLE related, just blink a LED. all evt examples shipped in original EVT package provided in 'Examples' dir.

To build the project, type `make`.

# NOTE

Ch584/ch585 firmware library use a private extended instruction 'mcpy' in `RVMSIS/core_riscv.h` as:

```
__attribute__((always_inline)) RV_STATIC_INLINE void __MCPY(void *dst, void *start, void *end)
{                                                                                                             __asm volatile("mcpy %2, %0, %1" : \
                   "+r"(start), "+r"(dst) : "r"(end) : "memory");
 }

```

To build ch584/ch585 project, you have to use [MRS toolchain](http://file-oss.mounriver.com/tools/MRS_Toolchain_Linux_x64_V1.92.1.tar.xz) instead of building gcc from riscv-gnu-toolchain or prebuilt xpack toolchain, etc.
