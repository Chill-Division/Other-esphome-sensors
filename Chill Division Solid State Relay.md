## Chill Division Solid State Relay

<pre>
# Relay, toggle it on / off
switch:
  - platform: gpio
    pin: 16
    id: Pump
    name: "Pump"
    icon: mdi:water-pump
  - platform: gpio
    pin: 17
    id: UnderCanopy
    name: "UnderCanopy"
    icon: mdi:light-flood-up
</pre>
