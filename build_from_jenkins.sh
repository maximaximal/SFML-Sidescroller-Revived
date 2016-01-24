#!/bin/bash

/opt/chroots/debian_jessie_x32/mount_jenkins.sh


echo "Build BomberPi"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "mkdir -p /root/jenkins/workspace/sfml-sidescroller_x32/build"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "rm -f /root/jenkins/workspace/sfml-sidescroller_x32/build/sfml-sidescroller*"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/sfml-sidescroller_x32/build && cmake .. -DCMAKE_PREFIX_PATH=/usr/local/lib/cmake -DSFML_SIDESCROLLER_VERSION_PATCH="\""$(cat /var/lib/jenkins/jobs/sfml-sidescroller_x32/nextBuildNumber)"\"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/sfml-sidescroller_x32/build && make"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/sfml-sidescroller_x32/build && make package"

echo "Add the package to the repository"
PIGA_DEB="$(ls /var/lib/jenkins/workspace/sfml-sidescroller_x32/build/*deb)"
echo "DEBFILE: $PIGA_DEB"
cd /media/maximaximal.com/www/repos/apt/debian && sudo reprepro includedeb jessie "$PIGA_DEB"

/opt/chroots/debian_jessie_x32/umount_jenkins.sh
