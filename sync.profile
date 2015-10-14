%modules = ( # path to module name map
    "Qt3DCore" => "$basedir/src/core",
    "Qt3DRenderer" => "$basedir/src/render",
    "Qt3DQuick" => "$basedir/src/quick3d/quick3d",
    "Qt3DQuickRenderer" => "$basedir/src/quick3d/quick3drenderer",
    "Qt3DInput" => "$basedir/src/input",
    "Qt3DLogic" => "$basedir/src/logic",
    "Qt3DCollision" => "$basedir/src/collision",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);

# Force generation of camel case headers for classes inside Qt3D* namespaces
$publicclassregexp = "Qt3D.*::.+";

# Module dependencies.
# Every module that is required to build this module should have one entry.
# Each of the module version specifiers can take one of the following values:
#   - A specific Git revision.
#   - any git symbolic ref resolvable from the module's repository (e.g. "refs/heads/master" to track master branch)
#
%dependencies = (
    "qtbase" => "",
    "qtxmlpatterns" => "",
    "qtdeclarative" => "",
    "qtimageformats" => "",
);
