# -*- mode: ruby -*-
# vi: set ft=ruby :



Vagrant.configure(2) do |config|
  config.vm.box = "ubuntu/trusty64"
  # config.vm.box = "ubuntu/xenial64"

  config.vm.provider "virtualbox" do |vb|
    vb.memory = "1024"
  end

  config.vm.provision "shell", name: 'install', inline: <<-SHELL
    sudo apt-add-repository -y ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get upgrade -y
    sudo apt-get install -y ninja-build g++-6 g++-6-multilib libstdc++6-6-dbg
  SHELL

  config.vm.provision "shell", name: 'install2', privileged: false, inline: <<-SHELL
  SHELL

  config.vm.provision "build", type: "shell", privileged: false, inline: <<-SHELL

    pwd

    export LD_LIBRARY_PATH=$PWD/lib
    echo $LD_LIBRARY_PATH
    echo $PATH

    rm -Rf build-*
    mkdir -p build-clang-libc++ build-clang-libstdc++ build-gcc6-libstdc++

    pushd build-clang-libc++
    cmake /vagrant -GNinja -DCMAKE_TOOLCHAIN_FILE=/vagrant/tools/linux-clang-libc++.cmake && ninja && ninja test
    popd

    pushd build-clang-libstdc++
    cmake /vagrant -GNinja -DCMAKE_TOOLCHAIN_FILE=/vagrant/tools/linux-clang-libstdc++.cmake && ninja && ninja test
    popd

    pushd build-gcc6-libstdc++
    CC=gcc-6 CXX=g++-6 cmake /vagrant -GNinja && ninja && ninja test
    popd

  SHELL
end
