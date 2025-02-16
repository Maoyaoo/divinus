![OpenIPC logo][logo]

## Divinus
**_Divinus is a new open source, multi-platform streamer_**

### Inner workings

This project strives to adopt a KISS "keep it simple, stupid!" structure while being as portable as can be.

Compared to most streamer software solutions available to this day, it attaches to the application-specific peripherals of a system-on-a-chip using an easy to understand HAL platform (hardware abstraction layer) proper to each chip series it supports.

Since it is exclusively using dynamic linking, its executable remains particularly compact and can be run on a multitude of environments, including in a tethered context (e.g. running from a temporary filesystem on read-only systems).

In spite of these design choices, Divinus boasts numerous features that cater to a wide range of uses you will be able to make of it.


### Supported hardware and features

| SoC Family              | Audio Stream | JPEG Snapshot | fMP4 Stream | RTSP Stream | On-Screen Display* |
|-------------------------|:------------:|:-------------:|:-----------:|:-----------:|:------------------:|
| GM813x                  | ↻            | ✔️           | ✔️          | ↻           | ↻                 |
| Hi3516CV300[^1]         | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| Hi3516CV500[^2]         | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| Hi3516EV200[^3]         | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| GK7205V200[^4]          | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| Hi3519V100[^5]          | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| Hi3519AV100             | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| Hi3559AV100             | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| T31 series              | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| infinity6[^6]           | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| infinity6b0[^7]         | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| infinity6e[^8]          | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| infinity6c[^9]          | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |
| infinity6f[^10]         | ↻            | ✔️           | ✔️          | ✔️          | ✔️                |

_✔️ - supported, ↻ - in development, ✗ - unsupported, ⁿ/ₐ - not supported by hardware_

_* At the moment, only text, 24-bit and 32-bit RGB overlays are handled, matricial formats and covers are to follow_

[^1]: Hi3516CV300 and Hi3516EV100
[^2]: Hi3516AV300, Hi3516CV500 and Hi3516DV300
[^3]: Hi3516DV200, Hi3516EV200/300 and Hi3518EV300
[^4]: GK7202V300, GK7205V200/300 and GK7605V100
[^5]: Hi3516AV200 and Hi3519V101
[^6]: SSC323, SSC325(D/DE) and SSC327(D/DE/Q)
[^7]: SSC333/35/37(DE)
[^8]: SSC30K\[D/Q\], SSC336\[D/Q\], SSC338\[D/G/Q\] and SSC339G
[^9]: SSC377(D/DE/QE) or SSC378\[DE/QE\]
[^10]: SSC379G


### Documentation

- [Overlays](doc/overlays.md) - _doc/overlays.md_


### Roadmap

- [ ] Audio stream (G.711 over RTSP, industry-supported lossy codec for MP4)
- [ ] Assorted WebUI to handle media reconfiguration and live preview
- [ ] Motion detection reimplementation
- [ ] Hardware support improvement (older SoCs, general usage chips)


### Technical support and donations

Please **_[support our project](https://openipc.org/support-open-source)_** with donations or orders for development or maintenance. Thank you!


[logo]: https://openipc.org/assets/openipc-logo-black.svg
