use strict;
our %detector;
our %configuration;

use Getopt::Long;
use Math::Trig;

my $DetectorMother="root";

my $DetectorName = 'compton_LD2_cryo_kapton';

sub compton_LD2_cryo_kapton
{
hinda();
target();
cryostat();
Kapton_cell();
}

sub hinda
{
 my $NUM  = 8;
 
 my @angle=(40,75,110,145,-55,-90,-125,-159);
 my @rot=(-40,-75,-110,-145,55,90,125,159); 
 
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
    
    my $x    = $dis_hindashield*sin($angle[$n-1]/180*3.1416);
    my $z    = $dis_hindashield*cos($angle[$n-1]/180*3.1416);   
    
    $detector{"name"}        = "$DetectorName\_hindacore\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x*cm $height*cm $z*cm";
    $detector{"rotation"}   = "0*deg $rot[$n-1]*deg 0*deg";
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
    $detector{"pos"}        = "$x*cm $height*cm $z*cm";
    $detector{"rotation"}   = "0*deg $rot[$n-1]*deg 0*deg";
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
     
     

    $x    = $dis_leadshield*sin($angle[$n-1]/180*3.1416);
    $z    = $dis_leadshield*cos($angle[$n-1]/180*3.1416);   
    
    $detector{"name"}        = "$DetectorName\_leadshield\_$n";
    $detector{"mother"}      = "$DetectorMother" ;
    $detector{"description"} = $detector{"name"};
    $detector{"pos"}        = "$x*cm $height*cm $z*cm";
    $detector{"rotation"}   = "0*deg $rot[$n-1]*deg 0*deg";
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
 $detector{"pos"}        = "0*cm 0*cm 0*cm";
 $detector{"rotation"}   = "0*deg 0*deg 0*deg";
 $detector{"color"}      = "2200cc";
 $detector{"type"}       = "Cons";
 $detector{"dimensions"} = "0*inch 1.068*inch 0*inch 0.792*inch 10*cm 0*deg 360*deg";
 $detector{"material"}   = "2H_gas";
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

sub cryostat
{
 my $N_cryo = 3;

 my @Rin_cryo = (6.96, 7.96, 8.96);
 my @Rout_cryo = (7.0, 8.0, 9.0);
 my @Dz_cryoWall = (6, 11, 14);
 my @dis_cryoWall = (3, 4, 6);
 my @Dz_cryoPlate = (0.02, 0.02, 0.25);
 my @dis_cryoPlate = (-3.02, -7.02, -8.25);
 my @dis_KaptonWindow = (6.98, 7.98, 8.98);

 for(my $l=1; $l<=$N_cryo; $l++)
 {   
     my %detector=init_det();
     $detector{"name"}        = "$DetectorName\_cryoWall\_$l";
     $detector{"mother"}      = "$DetectorMother" ;
     $detector{"description"} = $detector{"name"};
     $detector{"pos"}        = "0*inch $dis_cryoWall[$l-1]*inch 0*inch";
     $detector{"rotation"}   = "90*deg 0*deg 0*deg";
     $detector{"color"}      = "099000";
     $detector{"type"}       = "Tube";
     $detector{"dimensions"} = "$Rin_cryo[$l-1]*inch $Rout_cryo[$l-1]*inch $Dz_cryoWall[$l-1]*inch 0*deg 360*deg";
     $detector{"material"}   = "G4_Al";
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

     $detector{"name"}        = "$DetectorName\_cryoPlate\_$l";
     $detector{"mother"}      = "$DetectorMother" ;
     $detector{"description"} = $detector{"name"};
     $detector{"pos"}        = "0*inch $dis_cryoPlate[$l-1]*inch 0*inch";
     $detector{"rotation"}   = "90*deg 0*deg 0*deg";
     $detector{"color"}      = "099000";
     $detector{"type"}       = "Tube";
     $detector{"dimensions"} = "0*inch $Rout_cryo[$l-1]*inch $Dz_cryoPlate[$l-1]*inch 0*deg 360*deg";
     $detector{"material"}   = "G4_Al";
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

     $detector{"name"}        = "$DetectorName\_cryoFrontWindow\_$l";
     $detector{"mother"}      = "$DetectorMother" ;
     $detector{"description"} = $detector{"name"};
     $detector{"pos"}        = "0*inch 0*inch $dis_KaptonWindow[$l-1]*inch";
     $detector{"rotation"}   = "0*deg 0*deg 0*deg";
     $detector{"color"}      = "990000";
     $detector{"type"}       = "Tube";
     $detector{"dimensions"} = "0*inch 1.0*inch 0.02*inch 0*deg 360*deg";
     $detector{"material"}   = "G4_KAPTON";
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

     $detector{"name"}        = "$DetectorName\_cryoBackWindow\_$l";
     $detector{"mother"}      = "$DetectorMother" ;
     $detector{"description"} = $detector{"name"};
     $detector{"pos"}        = "0*inch 0*inch -$dis_KaptonWindow[$l-1]*inch";
     $detector{"rotation"}   = "0*deg 0*deg 0*deg";
     $detector{"color"}      = "990000";
     $detector{"type"}       = "Tube";
     $detector{"dimensions"} = "0*inch 1.0*inch 0.02*inch 0*deg 360*deg";
     $detector{"material"}   = "G4_KAPTON";
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



sub Kapton_cell
{

 my %detector=init_det();
 $detector{"name"}        = "$DetectorName\_KaptonCellWall";
 $detector{"mother"}      = "$DetectorMother" ;
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}        = "0*cm 0*cm 0*cm";
 $detector{"rotation"}   = "0*deg 0*deg 0*deg";
 $detector{"color"}      = "990000";
 $detector{"type"}       = "Cons";
 $detector{"dimensions"} = "1.068*inch 1.073*inch 0.792*inch 0.797*inch 10*cm 0*deg 360*deg";
 $detector{"material"}   = "G4_KAPTON";
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

 $detector{"name"}        = "$DetectorName\_KaptonFrontCap";
 $detector{"mother"}      = "$DetectorMother" ;
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}        = "0*cm 0*cm -10.00635*cm";
 $detector{"rotation"}   = "0*deg 0*deg 0*deg";
 $detector{"color"}      = "990000";
 $detector{"type"}       = "Tube";
 $detector{"dimensions"} = "0.*inch 1.068*inch 0.0025*inch 0*deg 360*deg";
 $detector{"material"}   = "G4_KAPTON";
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

 $detector{"name"}        = "$DetectorName\_KaptonBackCap";
 $detector{"mother"}      = "$DetectorMother" ;
 $detector{"description"} = $detector{"name"};
 $detector{"pos"}        = "0*cm 0*cm 10.00635*cm";
 $detector{"rotation"}   = "0*deg 0*deg 0*deg";
 $detector{"color"}      = "990000";
 $detector{"type"}       = "Tube";
 $detector{"dimensions"} = "0.*inch 0.792*inch 0.0025*inch 0*deg 360*deg";
 $detector{"material"}   = "G4_KAPTON";
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
