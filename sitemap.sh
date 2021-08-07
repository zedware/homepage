#!/usr/bin/env bash

# Generate sitemap.xml
# 1. find all files excluding css, dwt, gif, git, etc. as files.txt
# 2. sort by names
# 3. run this script

echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
echo "<urlset xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd\" xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">"
while read line; do 
  echo "<url>"
  echo "<loc>""https://zedware.github.io/homepage/"$line"</loc>"
  echo "<lastmod>2021-08-19T17:29:18+00:00</lastmod>"
  echo "</url>"
done < files.txt

echo "</urlset>"
