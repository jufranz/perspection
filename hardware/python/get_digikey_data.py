import microdata
import urllib2
import sys

output_scr = open("/tmp/get_digikey_data.scr", "w+")

if len(sys.argv) != 2:
    print "error: invalid number of inputs"
    print "usage: python get_digikey_data.py [url]"
    sys.exit(1)

url = sys.argv[1]
headers = { 'User-Agent' : 'Mozilla/5.0' }
postdata = None
#if not url.endswith(".html"):
#    url += ".html"
try:
    req = urllib2.Request(url, postdata, headers)
    data = urllib2.urlopen(req).read()
    items = microdata.get_items(data)
except:
    print "error: invalid url or unable to connect"
    sys.exit(1)

d = next(item for item in items if item.itemtype[0] == microdata.URI("http://schema.org/WebPage")).json_dict()
#d = item.json_dict()
DIST_NAME = "Digi-Key"
DIST_PN = d['properties']['mainEntity'][0]['properties']['productID'][0][4:].encode('ascii','ignore').strip()
MFG_NAME = d['properties']['mainEntity'][0]['properties']['manufacturer'][0].encode('ascii','ignore').strip()
MFG_PN = d['properties']['mainEntity'][0]['properties']['model'][0].encode('ascii','ignore').strip()
DESC = d['properties']['mainEntity'][0]['properties']['description'][0].encode('ascii','ignore').strip().replace('\n', '<br>')
print "DIST_NAME: " + DIST_NAME
print "DIST_PN: " + DIST_PN
print "MFG_NAME: " + MFG_NAME
print "MFG_PN: " + MFG_PN
print "DESC: " + DESC

output_scr.write("attribute DIST_NAME '" + DIST_NAME + "'\n")
output_scr.write("attribute DIST_PN '" + DIST_PN + "'\n")
output_scr.write("attribute MFG_NAME '" + MFG_NAME + "'\n")
output_scr.write("attribute MFG_PN '" + MFG_PN + "'\n")
output_scr.write("description '" + DESC + "<br><a href=\"" + url + "\">Digi-key Page</a>';\n")

output_scr.close()
