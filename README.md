# AirPressureMonitor

This ESP script is a small HTTP server that allows us to query the PSI air pressure of our air system remotely.

Sensor we used: [AUTEX 150 Psi Pressure Transducer/Sender/Sensor 150/200 Psi Stainless Steel 1/8”-27 NPT Pressure Transducer Sensor Compatible With Oil, Fuel, Air, Water](https://www.amazon.com/dp/B00NIK98O8)

Before compiling, rename `WifiCredentials.h.example` to `WifiCredentials.h`.

When you query the device, you get back a JSON response of the device uptime, and the PSI.

```json
{
  "uptime": 5526,
  "psi": 150
}
```
