<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.4.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="perspection">
<packages>
<package name="TI-VQFN-48">
<smd name="PAD" x="0" y="0" dx="4.1" dy="4.1" layer="1" cream="no"/>
<smd name="1" x="-2.75" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="2" x="-2.25" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="3" x="-1.75" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="4" x="-1.25" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="5" x="-0.75" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="6" x="-0.25" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="7" x="0.25" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="8" x="0.75" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="9" x="1.25" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="10" x="1.75" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="11" x="2.25" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="12" x="2.75" y="-3.475" dx="0.85" dy="0.28" layer="1" rot="R90"/>
<smd name="13" x="3.475" y="-2.75" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="14" x="3.475" y="-2.25" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="15" x="3.475" y="-1.75" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="16" x="3.475" y="-1.25" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="17" x="3.475" y="-0.75" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="18" x="3.475" y="-0.25" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="19" x="3.475" y="0.25" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="20" x="3.475" y="0.75" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="21" x="3.475" y="1.25" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="22" x="3.475" y="1.75" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="23" x="3.475" y="2.25" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="24" x="3.475" y="2.75" dx="0.85" dy="0.28" layer="1" rot="R180"/>
<smd name="25" x="2.75" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="26" x="2.25" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="27" x="1.75" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="28" x="1.25" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="29" x="0.75" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="30" x="0.25" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="31" x="-0.25" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="32" x="-0.75" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="33" x="-1.25" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="34" x="-1.75" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="35" x="-2.25" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="36" x="-2.75" y="3.475" dx="0.85" dy="0.28" layer="1" rot="R270"/>
<smd name="37" x="-3.475" y="2.75" dx="0.85" dy="0.28" layer="1"/>
<smd name="38" x="-3.475" y="2.25" dx="0.85" dy="0.28" layer="1"/>
<smd name="39" x="-3.475" y="1.75" dx="0.85" dy="0.28" layer="1"/>
<smd name="40" x="-3.475" y="1.25" dx="0.85" dy="0.28" layer="1"/>
<smd name="41" x="-3.475" y="0.75" dx="0.85" dy="0.28" layer="1"/>
<smd name="42" x="-3.475" y="0.25" dx="0.85" dy="0.28" layer="1"/>
<smd name="43" x="-3.475" y="-0.25" dx="0.85" dy="0.28" layer="1"/>
<smd name="44" x="-3.475" y="-0.75" dx="0.85" dy="0.28" layer="1"/>
<smd name="45" x="-3.475" y="-1.25" dx="0.85" dy="0.28" layer="1"/>
<smd name="46" x="-3.475" y="-1.75" dx="0.85" dy="0.28" layer="1"/>
<smd name="47" x="-3.475" y="-2.25" dx="0.85" dy="0.28" layer="1"/>
<smd name="48" x="-3.475" y="-2.75" dx="0.85" dy="0.28" layer="1"/>
<circle x="-3.8" y="-3.8" radius="0.2" width="0.12" layer="21"/>
<polygon width="0" layer="31">
<vertex x="-0.575" y="2.025"/>
<vertex x="0.575" y="2.025"/>
<vertex x="0.575" y="0.875"/>
<vertex x="-0.575" y="0.875"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.575" y="0.575"/>
<vertex x="0.575" y="0.575"/>
<vertex x="0.575" y="-0.575"/>
<vertex x="-0.575" y="-0.575"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.575" y="-2.025"/>
<vertex x="-0.575" y="-2.025"/>
<vertex x="-0.575" y="-0.875"/>
<vertex x="0.575" y="-0.875"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.875" y="2.025"/>
<vertex x="2.025" y="2.025"/>
<vertex x="2.025" y="0.875"/>
<vertex x="0.875" y="0.875"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.875" y="0.575"/>
<vertex x="2.025" y="0.575"/>
<vertex x="2.025" y="-0.575"/>
<vertex x="0.875" y="-0.575"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.025" y="-2.025"/>
<vertex x="0.875" y="-2.025"/>
<vertex x="0.875" y="-0.875"/>
<vertex x="2.025" y="-0.875"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.875" y="-2.025"/>
<vertex x="-2.025" y="-2.025"/>
<vertex x="-2.025" y="-0.875"/>
<vertex x="-0.875" y="-0.875"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.875" y="-0.575"/>
<vertex x="-2.025" y="-0.575"/>
<vertex x="-2.025" y="0.575"/>
<vertex x="-0.875" y="0.575"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.025" y="2.025"/>
<vertex x="-0.875" y="2.025"/>
<vertex x="-0.875" y="0.875"/>
<vertex x="-2.025" y="0.875"/>
</polygon>
<wire x1="-3.5" y1="3.5" x2="-3" y2="3.5" width="0.12" layer="21"/>
<wire x1="3" y1="3.5" x2="3.5" y2="3.5" width="0.12" layer="21"/>
<wire x1="3.5" y1="3.5" x2="3.5" y2="3" width="0.12" layer="21"/>
<wire x1="3.5" y1="-3" x2="3.5" y2="-3.5" width="0.12" layer="21"/>
<wire x1="3.5" y1="-3.5" x2="3" y2="-3.5" width="0.12" layer="21"/>
<wire x1="-3" y1="-3.5" x2="-3.5" y2="-3.5" width="0.12" layer="21"/>
<wire x1="-3.5" y1="-3.5" x2="-3.5" y2="-3" width="0.12" layer="21"/>
<wire x1="-3.5" y1="3" x2="-3.5" y2="3.5" width="0.12" layer="21"/>
<text x="-4" y="4" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<wire x1="-3.5" y1="3.5" x2="3.5" y2="3.5" width="0.12" layer="37"/>
<wire x1="3.5" y1="3.5" x2="3.5" y2="-3.5" width="0.12" layer="37"/>
<wire x1="3.5" y1="-3.5" x2="-3.5" y2="-3.5" width="0.12" layer="37"/>
<wire x1="-3.5" y1="-3.5" x2="-3.5" y2="3.5" width="0.12" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
</package>
<package name="L0402">
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-1" y="1" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<polygon width="0" layer="51">
<vertex x="-0.5" y="0.25"/>
<vertex x="0.5" y="0.25"/>
<vertex x="0.5" y="-0.25"/>
<vertex x="-0.5" y="-0.25"/>
</polygon>
<wire x1="-1" y1="0.4" x2="1" y2="0.4" width="0.1" layer="37"/>
<wire x1="1" y1="0.4" x2="1" y2="-0.4" width="0.1" layer="37"/>
<wire x1="1" y1="-0.4" x2="-1" y2="-0.4" width="0.1" layer="37"/>
<wire x1="-1" y1="-0.4" x2="-1" y2="0.4" width="0.1" layer="37"/>
<text x="0" y="0" size="0.5" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
<circle x="0" y="0" radius="0.1" width="0.12" layer="21"/>
</package>
<package name="L0603">
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-1.4" y="1" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<polygon width="0" layer="51">
<vertex x="-0.8" y="0.4"/>
<vertex x="0.8" y="0.4"/>
<vertex x="0.8" y="-0.4"/>
<vertex x="-0.8" y="-0.4"/>
</polygon>
<wire x1="-1.4" y1="0.5" x2="1.4" y2="0.5" width="0.1" layer="37"/>
<wire x1="1.4" y1="0.5" x2="1.4" y2="-0.5" width="0.1" layer="37"/>
<wire x1="1.4" y1="-0.5" x2="-1.4" y2="-0.5" width="0.1" layer="37"/>
<wire x1="-1.4" y1="-0.5" x2="-1.4" y2="0.5" width="0.1" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
<circle x="0" y="0" radius="0.1" width="0.12" layer="21"/>
</package>
<package name="L0805">
<smd name="1" x="-0.95" y="0" dx="1.3" dy="1.5" layer="1"/>
<smd name="2" x="0.95" y="0" dx="1.3" dy="1.5" layer="1"/>
<text x="-1.6" y="1" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<polygon width="0" layer="51">
<vertex x="-1" y="0.625"/>
<vertex x="1" y="0.625"/>
<vertex x="1" y="-0.625"/>
<vertex x="-1" y="-0.625"/>
</polygon>
<wire x1="-1.6" y1="0.7" x2="1.6" y2="0.7" width="0.1" layer="37"/>
<wire x1="1.6" y1="0.7" x2="1.6" y2="-0.7" width="0.1" layer="37"/>
<wire x1="1.6" y1="-0.7" x2="-1.6" y2="-0.7" width="0.1" layer="37"/>
<wire x1="-1.6" y1="-0.7" x2="-1.6" y2="0.7" width="0.1" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
<circle x="0" y="0" radius="0.15" width="0.12" layer="21"/>
</package>
<package name="L1206">
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-2.2" y="1" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<polygon width="0" layer="51">
<vertex x="-1.6" y="0.8"/>
<vertex x="1.6" y="0.8"/>
<vertex x="1.6" y="-0.8"/>
<vertex x="-1.6" y="-0.8"/>
</polygon>
<wire x1="-2.2" y1="0.9" x2="2.2" y2="0.9" width="0.1" layer="37"/>
<wire x1="2.2" y1="0.9" x2="2.2" y2="-0.9" width="0.1" layer="37"/>
<wire x1="2.2" y1="-0.9" x2="-2.2" y2="-0.9" width="0.1" layer="37"/>
<wire x1="-2.2" y1="-0.9" x2="-2.2" y2="0.9" width="0.1" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
<circle x="0" y="0" radius="0.3" width="0.12" layer="21"/>
</package>
<package name="C0402">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;</description>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-1" y="1" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<wire x1="0" y1="0.4" x2="0" y2="-0.4" width="0.12" layer="21"/>
<polygon width="0" layer="51">
<vertex x="-0.5" y="0.25"/>
<vertex x="0.5" y="0.25"/>
<vertex x="0.5" y="-0.25"/>
<vertex x="-0.5" y="-0.25"/>
</polygon>
<wire x1="-1" y1="0.4" x2="1" y2="0.4" width="0.1" layer="37"/>
<wire x1="1" y1="0.4" x2="1" y2="-0.4" width="0.1" layer="37"/>
<wire x1="1" y1="-0.4" x2="-1" y2="-0.4" width="0.1" layer="37"/>
<wire x1="-1" y1="-0.4" x2="-1" y2="0.4" width="0.1" layer="37"/>
<text x="0" y="0" size="0.5" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
</package>
<package name="C0603">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;</description>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-1.4" y="1" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<polygon width="0" layer="51">
<vertex x="-0.8" y="0.4"/>
<vertex x="0.8" y="0.4"/>
<vertex x="0.8" y="-0.4"/>
<vertex x="-0.8" y="-0.4"/>
</polygon>
<wire x1="0" y1="0.4" x2="0" y2="-0.4" width="0.12" layer="21"/>
<wire x1="-1.4" y1="0.5" x2="1.4" y2="0.5" width="0.1" layer="37"/>
<wire x1="1.4" y1="0.5" x2="1.4" y2="-0.5" width="0.1" layer="37"/>
<wire x1="1.4" y1="-0.5" x2="-1.4" y2="-0.5" width="0.1" layer="37"/>
<wire x1="-1.4" y1="-0.5" x2="-1.4" y2="0.5" width="0.1" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
</package>
<package name="C0805">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;</description>
<smd name="1" x="-0.95" y="0" dx="1.3" dy="1.5" layer="1"/>
<smd name="2" x="0.95" y="0" dx="1.3" dy="1.5" layer="1"/>
<text x="-1.6" y="1" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<polygon width="0" layer="51">
<vertex x="-1" y="0.625"/>
<vertex x="1" y="0.625"/>
<vertex x="1" y="-0.625"/>
<vertex x="-1" y="-0.625"/>
</polygon>
<wire x1="0" y1="0.7" x2="0" y2="-0.7" width="0.12" layer="21"/>
<wire x1="-1.6" y1="0.7" x2="1.6" y2="0.7" width="0.1" layer="37"/>
<wire x1="1.6" y1="0.7" x2="1.6" y2="-0.7" width="0.1" layer="37"/>
<wire x1="1.6" y1="-0.7" x2="-1.6" y2="-0.7" width="0.1" layer="37"/>
<wire x1="-1.6" y1="-0.7" x2="-1.6" y2="0.7" width="0.1" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
</package>
<package name="C1206">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;</description>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-2.2" y="1" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<polygon width="0" layer="51">
<vertex x="-1.6" y="0.8"/>
<vertex x="1.6" y="0.8"/>
<vertex x="1.6" y="-0.8"/>
<vertex x="-1.6" y="-0.8"/>
</polygon>
<wire x1="0" y1="0.8" x2="0" y2="-0.8" width="0.12" layer="21"/>
<wire x1="-2.2" y1="0.9" x2="2.2" y2="0.9" width="0.1" layer="37"/>
<wire x1="2.2" y1="0.9" x2="2.2" y2="-0.9" width="0.1" layer="37"/>
<wire x1="2.2" y1="-0.9" x2="-2.2" y2="-0.9" width="0.1" layer="37"/>
<wire x1="-2.2" y1="-0.9" x2="-2.2" y2="0.9" width="0.1" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
</package>
<package name="C1210">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;</description>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="2.7" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="2.7" layer="1"/>
<text x="-2.2" y="1.7" size="0.8" layer="25" font="vector" ratio="15">&gt;NAME</text>
<wire x1="0" y1="1.3" x2="0" y2="-1.3" width="0.12" layer="21"/>
<polygon width="0" layer="51">
<vertex x="-1.6" y="1.25"/>
<vertex x="1.6" y="1.25"/>
<vertex x="1.6" y="-1.25"/>
<vertex x="-1.6" y="-1.25"/>
</polygon>
<wire x1="-2.2" y1="1.3" x2="2.2" y2="1.3" width="0.1" layer="37"/>
<wire x1="2.2" y1="1.3" x2="2.2" y2="-1.3" width="0.1" layer="37"/>
<wire x1="2.2" y1="-1.3" x2="-2.2" y2="-1.3" width="0.1" layer="37"/>
<wire x1="-2.2" y1="-1.3" x2="-2.2" y2="1.3" width="0.1" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
</package>
<package name="SMA-VERT">
<pad name="POS" x="0" y="0" drill="1.5"/>
<pad name="NEG2" x="2.54" y="2.54" drill="1.6"/>
<pad name="NEG3" x="2.54" y="-2.54" drill="1.6"/>
<pad name="NEG4" x="-2.54" y="-2.54" drill="1.6"/>
<pad name="NEG1" x="-2.54" y="2.54" drill="1.6"/>
<wire x1="-3.2" y1="-1" x2="-3.2" y2="1" width="0.254" layer="21"/>
<wire x1="-1" y1="3.2" x2="1" y2="3.2" width="0.254" layer="21"/>
<wire x1="3.2" y1="1" x2="3.2" y2="-1" width="0.254" layer="21"/>
<wire x1="1" y1="-3.2" x2="-1" y2="-3.2" width="0.254" layer="21"/>
<text x="-1" y="4" size="0.8" layer="21" font="vector" ratio="15">&gt;NAME</text>
<wire x1="-3.2" y1="3.2" x2="-3.2" y2="-3.2" width="0.254" layer="37"/>
<wire x1="-3.2" y1="-3.2" x2="3.2" y2="-3.2" width="0.254" layer="37"/>
<wire x1="3.2" y1="-3.2" x2="3.2" y2="3.2" width="0.254" layer="37"/>
<wire x1="3.2" y1="3.2" x2="-3.2" y2="3.2" width="0.254" layer="37"/>
<text x="0" y="0" size="0.8" layer="37" font="vector" ratio="15" align="center">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="A3L-LOC">
<wire x1="288.29" y1="3.81" x2="342.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="342.265" y1="3.81" x2="373.38" y2="3.81" width="0.1016" layer="94"/>
<wire x1="373.38" y1="3.81" x2="383.54" y2="3.81" width="0.1016" layer="94"/>
<wire x1="383.54" y1="3.81" x2="383.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="383.54" y1="8.89" x2="383.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="383.54" y1="13.97" x2="383.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="383.54" y1="19.05" x2="383.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="288.29" y1="3.81" x2="288.29" y2="24.13" width="0.1016" layer="94"/>
<wire x1="288.29" y1="24.13" x2="342.265" y2="24.13" width="0.1016" layer="94"/>
<wire x1="342.265" y1="24.13" x2="383.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="373.38" y1="3.81" x2="373.38" y2="8.89" width="0.1016" layer="94"/>
<wire x1="373.38" y1="8.89" x2="383.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="373.38" y1="8.89" x2="342.265" y2="8.89" width="0.1016" layer="94"/>
<wire x1="342.265" y1="8.89" x2="342.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="342.265" y1="8.89" x2="342.265" y2="13.97" width="0.1016" layer="94"/>
<wire x1="342.265" y1="13.97" x2="383.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="342.265" y1="13.97" x2="342.265" y2="19.05" width="0.1016" layer="94"/>
<wire x1="342.265" y1="19.05" x2="383.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="342.265" y1="19.05" x2="342.265" y2="24.13" width="0.1016" layer="94"/>
<text x="344.17" y="15.24" size="2.54" layer="94">&gt;DRAWING_NAME</text>
<text x="344.17" y="10.16" size="2.286" layer="94">&gt;LAST_DATE_TIME</text>
<text x="357.505" y="5.08" size="2.54" layer="94">&gt;SHEET</text>
<text x="343.916" y="4.953" size="2.54" layer="94">Sheet:</text>
<frame x1="0" y1="0" x2="387.35" y2="260.35" columns="8" rows="5" layer="94"/>
</symbol>
<symbol name="CC2650-GPIO48">
<pin name="DIO_0" x="-17.78" y="17.78" length="middle"/>
<pin name="DIO_1" x="-17.78" y="15.24" length="middle"/>
<pin name="DIO_2" x="-17.78" y="12.7" length="middle"/>
<pin name="DIO_3" x="-17.78" y="10.16" length="middle"/>
<pin name="DIO_4" x="-17.78" y="7.62" length="middle"/>
<pin name="DIO_5" x="-17.78" y="5.08" length="middle"/>
<pin name="DIO_6" x="-17.78" y="2.54" length="middle"/>
<pin name="DIO_7" x="-17.78" y="0" length="middle"/>
<pin name="DIO_8" x="-17.78" y="-2.54" length="middle"/>
<pin name="DIO_9" x="-17.78" y="-5.08" length="middle"/>
<pin name="DIO_10" x="-17.78" y="-7.62" length="middle"/>
<pin name="DIO_11" x="-17.78" y="-10.16" length="middle"/>
<pin name="DIO_12" x="-17.78" y="-12.7" length="middle"/>
<pin name="DIO_13" x="-17.78" y="-15.24" length="middle"/>
<pin name="DIO_14" x="-17.78" y="-17.78" length="middle"/>
<pin name="DIO_15" x="-17.78" y="-20.32" length="middle"/>
<pin name="DIO_16" x="17.78" y="17.78" length="middle" rot="R180"/>
<pin name="DIO_17" x="17.78" y="15.24" length="middle" rot="R180"/>
<pin name="DIO_18" x="17.78" y="12.7" length="middle" rot="R180"/>
<pin name="DIO_19" x="17.78" y="10.16" length="middle" rot="R180"/>
<pin name="DIO_20" x="17.78" y="7.62" length="middle" rot="R180"/>
<pin name="DIO_21" x="17.78" y="5.08" length="middle" rot="R180"/>
<pin name="DIO_22" x="17.78" y="2.54" length="middle" rot="R180"/>
<pin name="DIO_23" x="17.78" y="0" length="middle" rot="R180"/>
<pin name="DIO_24" x="17.78" y="-2.54" length="middle" rot="R180"/>
<pin name="DIO_25" x="17.78" y="-5.08" length="middle" rot="R180"/>
<pin name="DIO_26" x="17.78" y="-7.62" length="middle" rot="R180"/>
<pin name="DIO_27" x="17.78" y="-10.16" length="middle" rot="R180"/>
<pin name="DIO_28" x="17.78" y="-12.7" length="middle" rot="R180"/>
<pin name="DIO_29" x="17.78" y="-15.24" length="middle" rot="R180"/>
<pin name="DIO_30" x="17.78" y="-17.78" length="middle" rot="R180"/>
<wire x1="-12.7" y1="20.32" x2="12.7" y2="20.32" width="0.254" layer="94"/>
<wire x1="12.7" y1="20.32" x2="12.7" y2="-22.86" width="0.254" layer="94"/>
<wire x1="12.7" y1="-22.86" x2="-12.7" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-22.86" x2="-12.7" y2="20.32" width="0.254" layer="94"/>
<text x="-12.7" y="22.86" size="1.778" layer="95" ratio="15" rot="MR180">&gt;NAME</text>
<text x="-12.7" y="-25.4" size="1.778" layer="96" ratio="15">&gt;VALUE</text>
</symbol>
<symbol name="CC2650-CORE">
<pin name="JTAG_TMSC" x="-20.32" y="12.7" length="middle"/>
<pin name="JTAG_TCKC" x="-20.32" y="10.16" length="middle"/>
<pin name="!RESET" x="-20.32" y="7.62" length="middle"/>
<pin name="DCDC_SW" x="-20.32" y="0" length="middle"/>
<pin name="X32K_Q1" x="-20.32" y="-7.62" length="middle"/>
<pin name="DCOUPL" x="-20.32" y="-12.7" length="middle"/>
<pin name="X32K_Q2" x="-20.32" y="-10.16" length="middle"/>
<pin name="VSS" x="-20.32" y="-15.24" length="middle"/>
<pin name="VDDS" x="20.32" y="7.62" length="middle" rot="R180"/>
<pin name="VDDS2" x="20.32" y="12.7" length="middle" rot="R180"/>
<pin name="VDDS3" x="20.32" y="10.16" length="middle" rot="R180"/>
<pin name="VDDS_DCDC" x="20.32" y="5.08" length="middle" rot="R180"/>
<pin name="VDDR" x="20.32" y="2.54" length="middle" rot="R180"/>
<pin name="VDDR_RF" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="RF_P" x="20.32" y="-5.08" length="middle" rot="R180"/>
<pin name="RF_N" x="20.32" y="-7.62" length="middle" rot="R180"/>
<pin name="X24M_N" x="20.32" y="-12.7" length="middle" rot="R180"/>
<pin name="X24M_P" x="20.32" y="-15.24" length="middle" rot="R180"/>
<wire x1="-15.24" y1="15.24" x2="15.24" y2="15.24" width="0.254" layer="94"/>
<wire x1="15.24" y1="15.24" x2="15.24" y2="-17.78" width="0.254" layer="94"/>
<wire x1="15.24" y1="-17.78" x2="-15.24" y2="-17.78" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-17.78" x2="-15.24" y2="15.24" width="0.254" layer="94"/>
<text x="-15.24" y="17.78" size="1.778" layer="95" ratio="15" rot="MR180">&gt;NAME</text>
<text x="-15.24" y="-20.32" size="1.778" layer="96" ratio="15">&gt;VALUE</text>
</symbol>
<symbol name="L">
<wire x1="-5.08" y1="0" x2="-3.81" y2="1.27" width="0.254" layer="94" curve="-90"/>
<wire x1="-2.54" y1="0" x2="-3.81" y2="1.27" width="0.254" layer="94" curve="90"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94" curve="-90"/>
<wire x1="0" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94" curve="90"/>
<wire x1="0" y1="0" x2="1.27" y2="1.27" width="0.254" layer="94" curve="-90"/>
<wire x1="2.54" y1="0" x2="1.27" y2="1.27" width="0.254" layer="94" curve="90"/>
<wire x1="2.54" y1="0" x2="3.81" y2="1.27" width="0.254" layer="94" curve="-90"/>
<wire x1="5.08" y1="0" x2="3.81" y2="1.27" width="0.254" layer="94" curve="90"/>
<text x="-5.08" y="3.81" size="1.778" layer="95" rot="MR180">&gt;NAME</text>
<text x="-5.08" y="-1.27" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
<pin name="2" x="7.62" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-7.62" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="C">
<wire x1="0" y1="0" x2="0" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-2.032" width="0.1524" layer="94"/>
<text x="1.524" y="0.381" size="1.778" layer="95">&gt;NAME</text>
<text x="1.524" y="-4.699" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.032" y1="-2.032" x2="2.032" y2="-1.524" layer="94"/>
<rectangle x1="-2.032" y1="-1.016" x2="2.032" y2="-0.508" layer="94"/>
<pin name="1" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="COAX">
<wire x1="0" y1="-2.54" x2="-0.762" y2="-1.778" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-0.508" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0.508" x2="-0.762" y2="0.508" width="0.254" layer="94"/>
<wire x1="-0.762" y1="0.508" x2="-0.508" y2="0" width="0.254" layer="94"/>
<wire x1="-0.508" y1="0" x2="-0.762" y2="-0.508" width="0.254" layer="94"/>
<wire x1="-0.762" y1="-0.508" x2="-2.54" y2="-0.508" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="0" y2="0.508" width="0.3048" layer="94" curve="-79.611142" cap="flat"/>
<wire x1="-2.54" y1="-2.54" x2="0" y2="-0.508" width="0.3048" layer="94" curve="79.611142" cap="flat"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="3.302" size="1.778" layer="95">&gt;NAME</text>
<pin name="POS" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<pin name="NEG" x="2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="A3L-LOC" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A3, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="A3L-LOC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CC2560F128RGZ" prefix="U">
<gates>
<gate name=".2" symbol="CC2650-GPIO48" x="22.86" y="0" addlevel="always"/>
<gate name=".1" symbol="CC2650-CORE" x="-22.86" y="0" addlevel="must"/>
</gates>
<devices>
<device name="" package="TI-VQFN-48">
<connects>
<connect gate=".1" pin="!RESET" pad="35"/>
<connect gate=".1" pin="DCDC_SW" pad="33"/>
<connect gate=".1" pin="DCOUPL" pad="23"/>
<connect gate=".1" pin="JTAG_TCKC" pad="25"/>
<connect gate=".1" pin="JTAG_TMSC" pad="24"/>
<connect gate=".1" pin="RF_N" pad="2"/>
<connect gate=".1" pin="RF_P" pad="1"/>
<connect gate=".1" pin="VDDR" pad="45"/>
<connect gate=".1" pin="VDDR_RF" pad="48"/>
<connect gate=".1" pin="VDDS" pad="44"/>
<connect gate=".1" pin="VDDS2" pad="13"/>
<connect gate=".1" pin="VDDS3" pad="22"/>
<connect gate=".1" pin="VDDS_DCDC" pad="34"/>
<connect gate=".1" pin="VSS" pad="PAD"/>
<connect gate=".1" pin="X24M_N" pad="46"/>
<connect gate=".1" pin="X24M_P" pad="47"/>
<connect gate=".1" pin="X32K_Q1" pad="3"/>
<connect gate=".1" pin="X32K_Q2" pad="4"/>
<connect gate=".2" pin="DIO_0" pad="5"/>
<connect gate=".2" pin="DIO_1" pad="6"/>
<connect gate=".2" pin="DIO_10" pad="16"/>
<connect gate=".2" pin="DIO_11" pad="17"/>
<connect gate=".2" pin="DIO_12" pad="18"/>
<connect gate=".2" pin="DIO_13" pad="19"/>
<connect gate=".2" pin="DIO_14" pad="20"/>
<connect gate=".2" pin="DIO_15" pad="21"/>
<connect gate=".2" pin="DIO_16" pad="26"/>
<connect gate=".2" pin="DIO_17" pad="27"/>
<connect gate=".2" pin="DIO_18" pad="28"/>
<connect gate=".2" pin="DIO_19" pad="29"/>
<connect gate=".2" pin="DIO_2" pad="7"/>
<connect gate=".2" pin="DIO_20" pad="30"/>
<connect gate=".2" pin="DIO_21" pad="31"/>
<connect gate=".2" pin="DIO_22" pad="32"/>
<connect gate=".2" pin="DIO_23" pad="36"/>
<connect gate=".2" pin="DIO_24" pad="37"/>
<connect gate=".2" pin="DIO_25" pad="38"/>
<connect gate=".2" pin="DIO_26" pad="39"/>
<connect gate=".2" pin="DIO_27" pad="40"/>
<connect gate=".2" pin="DIO_28" pad="41"/>
<connect gate=".2" pin="DIO_29" pad="42"/>
<connect gate=".2" pin="DIO_3" pad="8"/>
<connect gate=".2" pin="DIO_30" pad="43"/>
<connect gate=".2" pin="DIO_4" pad="9"/>
<connect gate=".2" pin="DIO_5" pad="10"/>
<connect gate=".2" pin="DIO_6" pad="11"/>
<connect gate=".2" pin="DIO_7" pad="12"/>
<connect gate=".2" pin="DIO_8" pad="14"/>
<connect gate=".2" pin="DIO_9" pad="15"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="L" prefix="L" uservalue="yes">
<gates>
<gate name="G$1" symbol="L" x="0" y="0"/>
</gates>
<devices>
<device name="0402" package="L0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="0603" package="L0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="0805" package="L0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="1206" package="L1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="C" prefix="C" uservalue="yes">
<gates>
<gate name="G$1" symbol="C" x="0" y="0"/>
</gates>
<devices>
<device name="0402" package="C0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="0603" package="C0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="0805" package="C0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="1206" package="C1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="1210" package="C1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="" constant="no"/>
<attribute name="DIST_PN" value="" constant="no"/>
<attribute name="MFG_NAME" value="" constant="no"/>
<attribute name="MFG_PN" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SMA" prefix="J">
<description>CONN SMA JACK STR 50 OHM PCB</description>
<gates>
<gate name="G$1" symbol="COAX" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SMA-VERT">
<connects>
<connect gate="G$1" pin="NEG" pad="NEG1 NEG2 NEG3 NEG4"/>
<connect gate="G$1" pin="POS" pad="POS"/>
</connects>
<technologies>
<technology name="">
<attribute name="DIST_NAME" value="Digi-Key" constant="no"/>
<attribute name="DIST_PN" value="A97594-ND" constant="no"/>
<attribute name="MFG_NAME" value="TE Connectivity AMP Connectors" constant="no"/>
<attribute name="MFG_PN" value="5-1814832-1" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="perspection" deviceset="A3L-LOC" device=""/>
<part name="U1" library="perspection" deviceset="CC2560F128RGZ" device=""/>
<part name="L1" library="perspection" deviceset="L" device="0402" value="2.4nH"/>
<part name="C1" library="perspection" deviceset="C" device="0402" value="6.8pF"/>
<part name="C2" library="perspection" deviceset="C" device="0402" value="1pF"/>
<part name="C3" library="perspection" deviceset="C" device="0402" value="1pF"/>
<part name="C4" library="perspection" deviceset="C" device="0402" value="DNP"/>
<part name="C5" library="perspection" deviceset="C" device="0402" value="1pF"/>
<part name="C6" library="perspection" deviceset="C" device="0402" value="12pF"/>
<part name="L2" library="perspection" deviceset="L" device="0402" value="2.4nH"/>
<part name="L3" library="perspection" deviceset="L" device="0402" value="2nH"/>
<part name="L4" library="perspection" deviceset="L" device="0402" value="2nH"/>
<part name="GND1" library="perspection" deviceset="GND" device=""/>
<part name="GND2" library="perspection" deviceset="GND" device=""/>
<part name="GND3" library="perspection" deviceset="GND" device=""/>
<part name="GND4" library="perspection" deviceset="GND" device=""/>
<part name="J1" library="perspection" deviceset="SMA" device=""/>
<part name="GND5" library="perspection" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="0" y="0"/>
<instance part="U1" gate=".2" x="124.46" y="88.9"/>
<instance part="U1" gate=".1" x="185.42" y="149.86"/>
<instance part="L1" gate="G$1" x="226.06" y="157.48" rot="R90"/>
<instance part="C1" gate="G$1" x="226.06" y="172.72"/>
<instance part="C2" gate="G$1" x="226.06" y="134.62"/>
<instance part="C3" gate="G$1" x="238.76" y="147.32" rot="R90"/>
<instance part="C4" gate="G$1" x="256.54" y="134.62"/>
<instance part="C5" gate="G$1" x="276.86" y="134.62"/>
<instance part="C6" gate="G$1" x="299.72" y="139.7" rot="R90"/>
<instance part="L2" gate="G$1" x="238.76" y="139.7"/>
<instance part="L3" gate="G$1" x="266.7" y="139.7"/>
<instance part="L4" gate="G$1" x="287.02" y="139.7"/>
<instance part="GND1" gate="1" x="226.06" y="124.46"/>
<instance part="GND2" gate="1" x="256.54" y="124.46"/>
<instance part="GND3" gate="1" x="276.86" y="124.46"/>
<instance part="GND4" gate="1" x="226.06" y="180.34" rot="R180"/>
<instance part="J1" gate="G$1" x="312.42" y="139.7" rot="MR0"/>
<instance part="GND5" gate="1" x="307.34" y="132.08"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="C2" gate="G$1" pin="2"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="226.06" y1="129.54" x2="226.06" y2="127" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C4" gate="G$1" pin="2"/>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="256.54" y1="127" x2="256.54" y2="129.54" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C5" gate="G$1" pin="2"/>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="276.86" y1="127" x2="276.86" y2="129.54" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="1"/>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="226.06" y1="177.8" x2="226.06" y2="175.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="NEG"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="309.88" y1="137.16" x2="307.34" y2="137.16" width="0.1524" layer="91"/>
<wire x1="307.34" y1="137.16" x2="307.34" y2="134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="C3" gate="G$1" pin="1"/>
<pinref part="L1" gate="G$1" pin="1"/>
<wire x1="236.22" y1="147.32" x2="226.06" y2="147.32" width="0.1524" layer="91"/>
<wire x1="226.06" y1="147.32" x2="226.06" y2="149.86" width="0.1524" layer="91"/>
<wire x1="226.06" y1="147.32" x2="220.98" y2="147.32" width="0.1524" layer="91"/>
<wire x1="220.98" y1="147.32" x2="220.98" y2="144.78" width="0.1524" layer="91"/>
<junction x="226.06" y="147.32"/>
<wire x1="220.98" y1="144.78" x2="205.74" y2="144.78" width="0.1524" layer="91"/>
<pinref part="U1" gate=".1" pin="RF_P"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="L1" gate="G$1" pin="2"/>
<pinref part="C1" gate="G$1" pin="2"/>
<wire x1="226.06" y1="165.1" x2="226.06" y2="167.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="L3" gate="G$1" pin="1"/>
<pinref part="C4" gate="G$1" pin="1"/>
<wire x1="259.08" y1="139.7" x2="256.54" y2="139.7" width="0.1524" layer="91"/>
<wire x1="256.54" y1="139.7" x2="256.54" y2="137.16" width="0.1524" layer="91"/>
<wire x1="256.54" y1="139.7" x2="251.46" y2="139.7" width="0.1524" layer="91"/>
<wire x1="251.46" y1="139.7" x2="251.46" y2="147.32" width="0.1524" layer="91"/>
<junction x="256.54" y="139.7"/>
<pinref part="C3" gate="G$1" pin="2"/>
<wire x1="251.46" y1="147.32" x2="243.84" y2="147.32" width="0.1524" layer="91"/>
<junction x="251.46" y="139.7"/>
<pinref part="L2" gate="G$1" pin="2"/>
<wire x1="251.46" y1="139.7" x2="246.38" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="L3" gate="G$1" pin="2"/>
<pinref part="L4" gate="G$1" pin="1"/>
<wire x1="274.32" y1="139.7" x2="276.86" y2="139.7" width="0.1524" layer="91"/>
<pinref part="C5" gate="G$1" pin="1"/>
<wire x1="276.86" y1="139.7" x2="279.4" y2="139.7" width="0.1524" layer="91"/>
<wire x1="276.86" y1="137.16" x2="276.86" y2="139.7" width="0.1524" layer="91"/>
<junction x="276.86" y="139.7"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="L4" gate="G$1" pin="2"/>
<pinref part="C6" gate="G$1" pin="1"/>
<wire x1="297.18" y1="139.7" x2="294.64" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="C6" gate="G$1" pin="2"/>
<pinref part="J1" gate="G$1" pin="POS"/>
<wire x1="309.88" y1="139.7" x2="304.8" y2="139.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="L2" gate="G$1" pin="1"/>
<pinref part="C2" gate="G$1" pin="1"/>
<wire x1="231.14" y1="139.7" x2="226.06" y2="139.7" width="0.1524" layer="91"/>
<wire x1="226.06" y1="139.7" x2="226.06" y2="137.16" width="0.1524" layer="91"/>
<wire x1="226.06" y1="139.7" x2="220.98" y2="139.7" width="0.1524" layer="91"/>
<wire x1="220.98" y1="139.7" x2="220.98" y2="142.24" width="0.1524" layer="91"/>
<junction x="226.06" y="139.7"/>
<wire x1="220.98" y1="142.24" x2="205.74" y2="142.24" width="0.1524" layer="91"/>
<pinref part="U1" gate=".1" pin="RF_N"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
