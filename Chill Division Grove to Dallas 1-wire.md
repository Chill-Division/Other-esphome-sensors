## Chill Division Grove to Dallas 1-wire

<pre>
one_wire:
  - platform: gpio
    pin: 16

sensor:
  - platform: dallas_temp
    name: "Temperature"
    update_interval: 30s
    id: temperature
</pre>
