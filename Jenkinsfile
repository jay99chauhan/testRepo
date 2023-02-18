pipeline {

  agent any

  options {

    buildDiscarder logRotator(artifactDaysToKeepStr: '', artifactNumToKeepStr: '5', daysToKeepStr: '', numToKeepStr: '5')

  }

  stages {

    stage('Hello') {

      steps {

        sh '''

          bash /var/lib/jenkins/workspace/build-script /var/lib/jenkins/workspace/IRS_launcher_v2.5/IRSLauncher.pro  var/lib/jenkins/workspace/build/bin/

        '''

      }

    }

  }

}
