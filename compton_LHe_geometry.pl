use strict;
our %detector;
our %configuration;

use Getopt::Long;
use Math::Trig;

my $DetectorMother="root";

my $DetectorName = 'compton_LHe';

sub compton_LHe
{
hinda();
target();
}

sub hinda
{
 my $NUM  = 8;
 
 my @theta=(55,55,90,90,90,125,125,125);
 my @phi=(0,-90,0,-90,180,0,-90,180);
 my @rotY=(-55,0,-90,0,90,-125,0,125); 
 my @rotX=(0,-55,0,-90,0,0,-125,0);

 my $R_hindacore=10.375*2.54/2;
 my $Dz_hindacore=10.875*2.54/2;

 my $Rin_hindashield=13.843;
 my $Rout_hindashield=20.6375; 
 my $Dz_hindashield=12*2.54/2;
 
 my $R_leadshield=21.0363;
 my $Dz_leadshield=6*2.54/2;

 my $R1_paraffin=2.73*2.54;
 my $R2_paraffin=3.515*2.54;
 
 my $dis_leadshield=57.996+$Dz_leadshield;
 my $dis_hindashield=57.996+$Dz_leadshield*2+$Dz_hindashield;
 my $dis_scint=50; 
 
 my $height=0.0525*2.54;

 for(my $n=1; $n<=$NUM; $n++)
 {   
    my $id=0;
    
    my %detector=init_det();
    
    my $x    = $dis_hindashield*sin($theta[$n-1]/180*3.1416)*cos($phi[$n-1]/180*3.1416);
    my $z    = $dis_hindashield*cos($theta[$n-1]/180*3.1416);   
    my $y    = $height+$dis_hindashield*sin($theta[$n-1]/180*3.1416)*sin($phi[$n-1]/180*3.1416);   
    
    $detector{"name"}        = "$DetectorName\_hindacore\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x*cm $y*cm $z*cm";
    $detector{"rotation"}   = "$rotX[$n-1]*deg $rotY[$n-1]*deg 0*deg";
    $detector{"color"}      = "9900CC";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "0*cm $R_hindacore*cm $Dz_hindacore*cm 0*deg 360*deg";
    $detector{"material"}   = "G4_SODIUM_IODIDE";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "flux";
    $detector{"hit_type"}    = "flux";
    $id=$n*10+1;
    $detector{"identifiers"} = "id manual $id";
     print_det(\%configuration, \%detector);         
     
    $detector{"name"}        = "$DetectorName\_hindashield\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x*cm $y*cm $z*cm";
    $detector{"rotation"}   = "$rotX[$n-1]*deg $rotY[$n-1]*deg 0*deg";
    $detector{"color"}      = "990000";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "$Rin_hindashield*cm $Rout_hindashield*cm $Dz_hindashield*cm 0*deg 360*deg";
    $detector{"material"}   = "G4_SODIUM_IODIDE";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "flux";
    $detector{"hit_type"}    = "flux";
    $id=$n*10+2;
    $detector{"identifiers"} = "id manual $id";
     print_det(\%configuration, \%detector);   
     
#    $x    = $dis_scint*sin($theta[$n-1]/180*3.1416)*cos($phi[$n-1]/180*3.1416);
#    $z    = $dis_scint*cos($theta[$n-1]/180*3.1416)*cos($phi[$n-1]/180*3.1416);   
    $x    = $dis_scint*sin($theta[$n-1]/180*3.1416)*cos($phi[$n-1]/180*3.1416);
    $z    = $dis_scint*cos($theta[$n-1]/180*3.1416);   
    $y    = $height+$dis_scint*sin($theta[$n-1]/180*3.1416)*sin($phi[$n-1]/180*3.1416);   
     
    $detector{"name"}        = "$DetectorName\_scint\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x*cm $y*cm $z*cm";
    $detector{"rotation"}   = "$rotX[$n-1]*deg $rotY[$n-1]*deg 0*deg";
    $detector{"color"}      = "9955CC";
    $detector{"type"}       = "Box";
    $detector{"dimensions"} = "3*inch 3*inch 0.09375*inch";
    $detector{"material"}   = "G4_POLYETHYLENE";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "flux";
    $detector{"hit_type"}    = "flux";
    $id=$n*10+0;
    $detector{"identifiers"} = "id manual $id";
    if($n==2 || $n==4 || $n==7) {print_det(\%configuration, \%detector);        }
     

#    $x    = $dis_leadshield*sin($theta[$n-1]/180*3.1416)*cos($phi[$n-1]/180*3.1416);
#    $z    = $dis_leadshield*cos($theta[$n-1]/180*3.1416)*cos($phi[$n-1]/180*3.1416);   
    $x    = $dis_leadshield*sin($theta[$n-1]/180*3.1416)*cos($phi[$n-1]/180*3.1416);
    $z    = $dis_leadshield*cos($theta[$n-1]/180*3.1416);   
    $y    = $height+$dis_leadshield*sin($theta[$n-1]/180*3.1416)*sin($phi[$n-1]/180*3.1416);   
    
    $detector{"name"}        = "$DetectorName\_leadshield\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x*cm $y*cm $z*cm";
    $detector{"rotation"}   = "$rotX[$n-1]*deg $rotY[$n-1]*deg 0*deg";
    $detector{"color"}      = "000099";
    $detector{"type"}       = "Tube";
    $detector{"dimensions"} = "0*cm $R_leadshield*cm $Dz_leadshield*cm 0*deg 360*deg";
    $detector{"material"}   = "G4_Pb";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
     print_det(\%configuration, \%detector);   
     
   $detector{"name"}        = "$DetectorName\_paraffin\_$n";
    $detector{"mother"}      = "$DetectorName\_leadshield\_$n";
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm 0*cm";
    $detector{"rotation"}   = "0*deg 0*deg 0*deg";
    $detector{"color"}      = "009900";
    $detector{"type"}       = "Cons";
    $detector{"dimensions"} = "0*cm $R1_paraffin*cm 0*cm $R2_paraffin*cm  $Dz_leadshield*cm 0*deg 360*deg";
    $detector{"material"}   = "G4_PARAFFIN";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
     print_det(\%configuration, \%detector);       
 }
 
}

sub target
{ 
    my %detector=init_det();
    $detector{"name"}        = "$DetectorName\_target";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "0*cm 0*cm 0.024*inch";
    $detector{"rotation"}   = "0.728*deg 0*deg 0*deg";
    $detector{"color"}      = "2200cc";
    $detector{"type"}       = "Cons";
    $detector{"dimensions"} = "0*inch 1.068*inch 0*inch 0.792*inch 10*cm 0*deg 360*deg";
    $detector{"material"}   = "LD2";
    $detector{"mfield"}     = "no";
    $detector{"ncopy"}      = 1;
    $detector{"pMany"}       = 1;
    $detector{"exist"}       = 1;
    $detector{"visible"}     = 1;
    $detector{"style"}       = 1;
    $detector{"sensitivity"} = "no";
    $detector{"hit_type"}    = "no";
    $detector{"identifiers"} = "no";
     print_det(\%configuration, \%detector);   
}

