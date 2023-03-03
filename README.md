# Gatonegro's dwm

Custom build of [dwm](https://dwm.suckless.org/).

## Patches

+ **alpha** adds transparency to the status bar.
+ **attachbelow** adds new clients below the active client.
+ **bar_height** allows the bar height to be declared explicitly.
+ **center_transient_windows** aligns transient windows to the centre of the screen.
+ **cyclelayouts** cycles through all available layouts.
+ **dwmblocks** status bar (using `dwmblocks-async`).
+ **fancybar** shows the titles of all visible windows on the status bar.
+ **movestack** enables moving clients up and down the stack.
+ **noborder** removes the border when only one client window is visible.
+ **pertag** allows each tag to have its own layout, nmaster, etc.
+ **restartsig** allows `dwm` to be restarted instead of needing to log out.
+ **scratchpads** adds floating scratchpad windows.
+ **seamlessrestart** retains layouts, tags, nmaster, etc., across restarts.
+ **statuscmd** makes status elements clickable.
+ **shiftview_clients** cycles only through tags with visible clients.
+ **status2d** adds colour support to the status bar, includes **xrdb** support.
+ **sticky** tags windows to be visible on all tags.
+ **swallow** lets terminals swallow windows opened by a child process.
+ **systray** adds a systray to the status bar.
+ **togglelayout** enables the previous layout if the current layout's key is pressed.
+ **vanitygaps** adds configurable gaps between windows.
+ **xrdb** reads colours from Xresources at runtime.

## Layouts

+ **tile**
+ **monocle**
+ **deck**
+ **gridmode**
+ **centeredmaster**
+ **bstack**

## Extra features

+ `dwm.c` - Autostart function to launch or refresh `dwmblocks` whenever `dwm`
  (re)starts.
+ `systrayiconsize` added to `bar_systray` to allow explicitly declaring an
  icon size in `config.h` instead of calculating them from the font size.
+ Modified `width_systray` function in `bar_systray` to reduce horizontal
  padding.
