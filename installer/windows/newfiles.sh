#!/bin/bash
CWD=`pwd`
echo $CWD
OLDTORCS=/cygdrive/c/t2
NEWTORCS=$CWD/base

rm -f newfiles oldfiles diff edit

cd $NEWTORCS
find . > $CWD/newfiles
cd $OLDTORCS
find . > $CWD/oldfiles

cd $CWD
diff oldfiles newfiles > diff
sed -e 's/>[ ]*\.\/\(.*\)/File "base\\\1"/g' diff | sed 's/\//\\/g' > edit
