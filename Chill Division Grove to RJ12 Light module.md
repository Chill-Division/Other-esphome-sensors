## Chill Division Grove to RJ12 Light module

<pre>
output:
  - platform: ledc
    pin: 16
    frequency: 1000 hz
    id: pwm_output16
    inverted: true

light:
  - platform: monochromatic
    output: pwm_output16
    gamma_correct: 1.0
    name: "Light-FS"
    id: "Light_FS"
</pre>
