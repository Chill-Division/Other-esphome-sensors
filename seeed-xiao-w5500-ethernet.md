## Seeed Studio Xiao W5500 Ethernet Adapter

Setup as a bluetooth proxy over ethernet

<pre>
esphome:
  name: seed-xiao-w5500
  friendly_name: seed-xiao-w5500

esp32:
  variant: esp32s3
  framework:
    type: esp-idf

# Enable logging
logger:

# Enable Home Assistant API
api:
  encryption:
    key: "***"

ota:
  - platform: esphome
    password: "***"

ethernet:
  type: W5500
  clk_pin: GPIO7
  mosi_pin: GPIO9
  miso_pin: GPIO8
  cs_pin: GPIO2

bluetooth_proxy:
  active: True
</pre>
