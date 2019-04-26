// this is quick and dirty, please don't shame me
// I can do better!
// pull requests welcome

Gap = 0.12;
ExtrusionWidth = 0.48;
LayerHeight = 0.2;
Body = [20.8, 26.5, 12];
Wall = 2* ExtrusionWidth;
ShaftDiam = 6.78 + 2* Gap;
PotiPos = [Body.x/-2 +8, Body.y/2-10, 0];
MountOffsetFromTop = 25;
MountWidth = 14;

Epsilon = 0.01;

module main() {
    difference() {
        union() { // positive
            // housing +
            translate([0,0,Body.z/2+Wall])
                cube(Body + [2,1,1]*Wall, center=true);
            
            // X220 mount +
            translate([Body.x/2,-10,-1])
                cube([MountWidth+Wall-Epsilon, MountOffsetFromTop+20, 10]);
            // top part +
            translate([(Body.x+MountWidth+Wall-Epsilon)/2,MountOffsetFromTop+7,2])
                rotate([0,90,0])
                    cylinder(d=18, h=MountWidth+Wall-Epsilon, center=true, $fn=9);
            
        }
        union() { // negative
            // inside -
            translate([0,-1,0.5]*(Wall+Epsilon)+[0,0,Body.z/2+Wall])
                cube(Body, center=true);
            
            // poti -
            translate(PotiPos)
                cylinder(d=ShaftDiam, h=4*Body.z, center=true);
            
            // X220 mount -
            translate([MountWidth/2+Body.x/2+Wall,MountOffsetFromTop,0])
                rotate([0,90,0])
                    rotate([0,0,90])
                        #linear_extrude(MountWidth, center=true)
                            X220Bezel();
        }
    }
}

module X220Bezel() {
    baseThickness = 7.6 + Gap;
    topThickness = 11.5 + Gap;
    topRampH = 10;
    baseLength = 100;
    polygon([
        [-baseLength, 0],
        [0, 0],
        [topRampH, -topThickness + baseThickness],
        [topRampH, baseThickness],
        [-baseLength, baseThickness]
        ]);
}

$fn=92;

module knob() {
    ShaftDiam = 6.0 * (6/5.62) + Gap;
    ShaftAcross = 4.5 + Gap/2;
    ShaftLength = 9;
    KnobLength = 25;
    KnobBaseDiam = 20;
    notches = 11;
    
    difference() {
        union() {
            // Shaft Housing +
            cylinder(d=ShaftDiam+2*Wall, h=ShaftLength+Wall);
            
            // Knob Body +
            cylinder(d1=KnobBaseDiam, d2=KnobBaseDiam*0.6, h=KnobLength, $fn=notches);
            
        }
        translate([0,0,-Epsilon]) {
            // inside -
            difference() {
                cylinder(d=ShaftDiam, h=ShaftLength);
                translate([-ShaftDiam/2 + ShaftAcross, -ShaftDiam/2-Epsilon, -Epsilon])
                    cube((ShaftDiam+2*Epsilon)*[1,1,0]+[0,0,ShaftLength+2*Epsilon]);
            }
            // notches -
            for(i=[0:notches-1])
                rotate([0,0,360*(i+0.5)/notches])
                    translate([KnobBaseDiam/2+0.3,0,-10])
                        rotate([0,-4,0])
                            cylinder(d1=5, d2=2.6, h=KnobLength*3, center=true);
        }
    }
}

//knob();
main();