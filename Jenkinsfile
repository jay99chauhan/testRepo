pipeline {

  agent any

  options {

    buildDiscarder logRotator(artifactDaysToKeepStr: '', artifactNumToKeepStr: '5', daysToKeepStr: '', numToKeepStr: '5')

  }

  stages {

    stage('Hello') {

      steps {

        sh '''

          bash /var/lib/jenkins/workspace/build-script --pro-file-path /var/lib/jenkins/workspace/IRS_launcher_v2.5/IRSLauncher.pro --build-at /var/lib/jenkins/workspace/build/bin/ --qt-root /home/irs_jay/Qt --qt-version 5.15.2

        '''

      }

    }

  }
  
      post{
        always{
            mail to: "jagruti.vaswani@ishitva.in",
            subject: "Build Successful",
            body: "Completed the build please review once."
        }
    }

}
