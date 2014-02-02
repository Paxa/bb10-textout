unless RUBY_VERSION >= '1.9'
  raise "This script requires ruby version 1.9+, current is #{RUBY_VERSION}"
end

require 'pp'

# load qnx env variables, including PATH, DYLD_LIBRARY_PATH, MAKEFLAGS
def set_qnx_env
  return false if ENV['QNX_TARGET']

  system(%{
    export tmp_pwd=`pwd`
    cd /Applications/Momentics.app && source bbndk-* && cd $tmp_pwd
    unset tmp_pwd
  })
end

def symbolize(obj)
  return obj.inject({}){|memo,(k,v)| memo[k.to_sym] =  symbolize(v); memo} if obj.is_a? Hash
  return obj.inject([]){|memo,v    | memo           << symbolize(v); memo} if obj.is_a? Array
  return obj
end

DEPLOY_YML = {}

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

task :cmake do
  set_qnx_env

  Dir.chdir("build") do
    system %{ cmake -DCMAKE_TOOLCHAIN_FILE="./cmake/Toolchain-QNX-8.0.0.cmake" . }
  end
end

task :make do
  set_qnx_env

  Dir.chdir("build") do
    system %{ make }
  end
end

task :unix_makefile do
  set_qnx_env

  Dir.chdir("build") do
    system %{ cmake -DCMAKE_TOOLCHAIN_FILE="./cmake/Toolchain-QNX-8.0.0.cmake" -G "Unix Makefiles" . }
  end
end

task :dump_config do
  load_deploy_yml
  pp DEPLOY_YML
end

task :bar do
  set_qnx_env
  load_deploy_yml

  app, device = DEPLOY_YML[:app], DEPLOY_YML[:device]
  token = Shellwords.escape(DEPLOY_YML[:token][:path]).sub(/^\\~/, '~')

  cmd = "blackberry-nativepackager -package build/#{app[:bar_file]} bar-descriptor.xml -devMode -debugToken #{token}"
  puts cmd
  system cmd
end

task :install_app do
  set_qnx_env
  load_deploy_yml

  app, device, toekn = DEPLOY_YML[:app], DEPLOY_YML[:device], DEPLOY_YML[:token]

  system %{
    blackberry-deploy -installApp #{device[:ip]} -password #{device[:password]} build/#{app[:bar_file]}
  }
end

task :build do
  Rake::Task["cmake"].invoke
  Rake::Task["make"].invoke
end

task :deploy do
  Rake::Task["bar"].invoke
  Rake::Task["install_app"].invoke
end
