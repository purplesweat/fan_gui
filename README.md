# fan_gui

## A quick and dirty thinkpad fan graphical controller written with just C and GTK4

# Installation

In order to get the thinkpad fan working, make sure you have the kernel with a suitable thinkpad acpi patch (and enable it as a module if compiling your own kernel). If your distro does not happen to include it, compiling a kernel from gentoo's sources is recommended.

```Kconfig
Device Drivers  --->
    [*] X86 Platform Specific Device Drivers  ---> 
        <M>   ThinkPad ACPI Laptop Extras
```

Afterwards, change the modprobe configuration:

```bash
$ echo 'options thinkpad_acpi fan_control=1' | sudo tee /etc/modprobe.d/thinkpad.conf
```

To install the actual program, simply:

```bash
$ cd fan_gui
$ sudo make install
```
