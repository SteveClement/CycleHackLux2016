# Cycle Hack Luxembourg 2016 - Team Average Speed Pixel

This is the repo for the T-Shirt entry.

# Slides

*Soon…*

# Thoughts and barriers

We analyzed a few barriers we could overcome with this project. Foremost the barrier for the Car driver to instantly understand how fast the cyclist is going can be lowered with this project. With the graphical display of the cyclists speed with bright colors will tell the traffic that if the bar is red, the cyclist is probably slow. Orange indicating that we are at a medium pace and green finally tells traffic that we have reached cruising speed.
During peak traffic cars have an average speed of 17km/h in Luxembourg City. This was our metric to measure out the indications on the back of the T-Shirt.

# Data

There was no official data to be found on the average speed of traffic in Luxembourg City. Thus we mapped out various routes during various days and times and checked what platforms like Google Maps suggested car travel times were.

# Versatility

Whilst this is a Cycle project it can be used in a broader sense for any awareness raising campaign.

Some ideas were:

- Smart T-shirt for runners (show current speed or distance left)
- Display the current pollution level in traffic
- Display the current UV level in the sun
- *Your idea here*

# Caveats

This being a dirty prototype the main caveat is wash-ability. See the challenges section for more details.
Another major caveat is the fact that it is not backpack compatible. Most cyclists use a backpack thus would need a different solution to use this tool.
Further on the visibility of the text is only guaranteed during day time. This also gets attention in the challenges section.

# Challenges

# Hardware

## Micro-controller

The chosen platform for the prototype was an Adafruit FLORA v2.
This Arduino compatible board was ideal for the rapid prototyping of this project.

## Sensors

The only sensor currently in use is the Adafruit FLORA GPS module. This primarily serves as the source of the wearers speed.
But can also return an exact Lat/Lon position as well as the current time.

## LEDs

We used an 144LEDs per meter RGB NeoPixel strip from @Adafruit. Good for the initial prototype.
Additionally the Adafruit FLORA has an on-board NeoPixel that can be used for the current status.

# Next-gen Hardware

## Thoughts

Whilst the FLORA board is ideal for wearables we feel that adding the bulk of the GPS sensor makes it less versatile.
A design thought needs to be considered. Do you poll the users phone for location data and speed or use an external GPS module.
This needs to be tested in the lab to see how battery consumption works out with the different strategies.
What uses more power, Bluetooth LE or GPS (our un-educated guess would be GPS). But user acceptance might not be great knowing that their T-Shirt drains their phones' battery.

## Micro-Controller

The next prototype will be done with the Adafruit Feather platform. Specifically the Feather with the Bluetooth LE module and the Feather GPS module.

## Sensors

With the Adafruit Feather BLE we have Bluetooth on-board and only a GPS Module is required if needed. In addition to that a cheap pollution sensor will be added for testing.

## LEDs

The next version will include an 144LEDs per meter RGBW strip. Still based on NeoPixels but with Warm white.
Additionally the Adafruit FLORA has an on-board NeoPixel that can be used for the current status if you use that platform.

# After Cycle Hack

This entry earned the team a 6 month stay at #TechnoPort Esch-Belval. (:yay:)