pipeline {

  agent any

  options {

    buildDiscarder logRotator(artifactDaysToKeepStr: '', artifactNumToKeepStr: '5', daysToKeepStr: '', numToKeepStr: '5')

  }

  stages {

    stage('Hello') {

      steps {

        sh '''

          bash ./build-script /var/lib/jenkins/workspace/IRS_launcher_v2.5/IRSLauncher.pro  /home/irs_jay/build_destination

        '''

      }

    }

  }

}
