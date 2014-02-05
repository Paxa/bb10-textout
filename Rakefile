unless RUBY_VERSION >= '1.9'
  raise "This script requires ruby version 1.9+, current is #{RUBY_VERSION}"
end

require 'pp'

# load qnx env variables, including PATH, DYLD_LIBRARY_PATH, MAKEFLAGS
def set_qnx_env
  return false if ENV['QNX_TARGET']

  variables = %w[QNX_TARGET QNX_HOST QNX_CONFIGURATION MAKEFLAGS DYLD_LIBRARY_PATH PATH QDE CPUVARDIR]

  data = %x{
    tmp_pwd=`pwd`
    cd /Applications/Momentics.app && source bbndk-* && cd $tmp_pwd
    #{variables.map {|v| "echo $#{v} "}.join(";")}
  }

  data.split("\n").each_with_index do |value, i|
    ENV[ variables[i] ] = value
  end
end

def symbolize(obj)
  return obj.inject({}){|memo,(k,v)| memo[k.to_sym] =  symbolize(v); memo} if obj.is_a? Hash
  return obj.inject([]){|memo,v    | memo           << symbolize(v); memo} if obj.is_a? Array
  return obj
end

DEPLOY_YML = {}

# loads deploy.yml file to DEPLOY_YML constant
def load_deploy_yml
  if DEPLOY_YML.size > 0
    DEPLOY_YML
  else
    require 'yaml'
    require 'shellwords'

    DEPLOY_YML.replace symbolize(YAML::load_file("./deploy.yml"))
    #symbolize(DEPLOY_YML)
    DEPLOY_YML
  end
end

desc "Load bb10 env variables"
task :laodenv do
  set_qnx_env
end

task :get_mruby do
  Dir.chdir("build") do
    system %{
      rm -rf mruby
      git clone git@github.com:mruby/mruby.git
    }
  end
end

task :make_mruby do
  set_qnx_env

  Dir.chdir("build") do
    system %{
      cp build_config.rb mruby/build_config.rb
      cd mruby && ruby ./minirake
    }
  end
end

task :mruby do
  Rake::Task["get_mruby"].invoke
  Rake::Task["make_mruby"].invoke
end

desc "Run cmake command to create Makefile"
task :cmake do
  set_qnx_env

  Dir.chdir("build") do
    system %{ cmake -DCMAKE_TOOLCHAIN_FILE="./cmake/Toolchain-QNX-8.0.0.cmake" . }
  end
end

desc "Run make command"
task :make do
  set_qnx_env

  Dir.chdir("build") do
    system %{ make }
  end
end

desc "Generates Makefile"
task :unix_makefile do
  set_qnx_env

  Dir.chdir("build") do
    system %{ cmake -DCMAKE_TOOLCHAIN_FILE="./cmake/Toolchain-QNX-8.0.0.cmake" -G "Unix Makefiles" . }
  end
end

desc "Print loaded deploy.yml options"
task :dump_config do
  load_deploy_yml
  pp DEPLOY_YML
end

desc "Generate .bar application file"
task :bar do
  set_qnx_env
  load_deploy_yml

  app, device = DEPLOY_YML[:app], DEPLOY_YML[:device]
  token = Shellwords.escape(DEPLOY_YML[:token][:path]).sub(/^\\~/, '~')

  system %{
    rm -rf ./assets
    mkdir ./assets
    cp build/mruby/build/blackberry/bin/* ./assets
    blackberry-nativepackager -package build/#{app[:bar_file]} bar-descriptor.xml -devMode -debugToken #{token}
  }
end

desc "Send .bar file to device"
task :install_app do
  set_qnx_env
  load_deploy_yml

  app, device, toekn = DEPLOY_YML[:app], DEPLOY_YML[:device], DEPLOY_YML[:token]

  system %{
    blackberry-deploy -installApp #{device[:ip]} -password #{device[:password]} build/#{app[:bar_file]}
  }
end

desc "compile app (cmake & make)"
task :build do
  Rake::Task["cmake"].invoke
  Rake::Task["make"].invoke
end

desc "cook .bar and install to device (bar & install_app)"
task :deploy do
  Rake::Task["bar"].invoke
  Rake::Task["install_app"].invoke
end

task :clean do
  Dir.chdir("build") do
    system %{
      rm -rf CMakeCache.txt
      rm -rf CMakeFiles
      rm -rf cmake_install.cmake
      rm -rf TextOut
      rm -rf TextOut.bar
      rm -rf TextOut_automoc.cpp
      rm -rf moc_textoutapp.cpp
    }
  end
end
