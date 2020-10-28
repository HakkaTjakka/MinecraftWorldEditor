import com.github.jengelman.gradle.plugins.shadow.ShadowPlugin
import com.github.jengelman.gradle.plugins.shadow.tasks.ShadowJar
import nl.javadude.gradle.plugins.license.LicenseExtension
import nl.javadude.gradle.plugins.license.LicensePlugin
import org.ajoberstar.grgit.Grgit
import org.ajoberstar.grgit.operation.DescribeOp
import org.gradle.api.internal.HasConvention

buildscript {
    repositories {
        maven {
            setUrl("https://plugins.gradle.org/m2/")
        }
        maven {
            setUrl("https://libraries.minecraft.net")
        }
    }
    dependencies {
        classpath("org.ajoberstar:grgit:1.4.+")
        classpath("gradle.plugin.nl.javadude.gradle.plugins:license-gradle-plugin:0.13.1")
        classpath("com.github.jengelman.gradle.plugins:shadow:1.2.3")
    }
}

group = "io.github.opencubicchunks"
version = getProjectVersion()

val licenseYear = properties["licenseYear"] as String
val projectName = properties["projectName"] as String

val shadowJar: ShadowJar by tasks
val jar: Jar by tasks

apply {
    plugin<JavaPlugin>()
    plugin<MavenPlugin>()
    plugin<SigningPlugin>()
    plugin<LicensePlugin>()
    plugin<ShadowPlugin>()
}

val sourceSets = the<JavaPluginConvention>().sourceSets!!


configure<JavaPluginConvention> {
    setSourceCompatibility(JavaVersion.VERSION_1_8)
}


configure<LicenseExtension> {
    val ext = (this as HasConvention).convention.extraProperties
    ext["project"] = projectName
    ext["year"] = licenseYear
    exclude("**/*.info")
    exclude("**/package-info.java")
    exclude("**/*.json")
    exclude("**/*.xml")
    exclude("assets/*")
    header = file("HEADER.txt")
    ignoreFailures = false
    strictCheck = true
    mapping(mapOf("java" to "SLASHSTAR_STYLE"))
}

repositories {
    mavenCentral()
    maven {
        setUrl("https://oss.sonatype.org/content/groups/public/")
    }
    maven {
        name = "mojang"
        setUrl("https://libraries.minecraft.net/")
    }
}

dependencies {
    compile("com.flowpowered:flow-nbt:1.0.1-SNAPSHOT")
    compile("io.github.opencubicchunks:regionlib:0.63.0-SNAPSHOT")
    compile("com.carrotsearch:hppc:0.8.1")
    compile("com.google.guava:guava:27.0.1-jre")
    compile("com.mojang:brigadier:1.0.17")
    compile(project(":nbt"))
    testCompile("junit:junit:4.11")
}

jar.apply {
    manifest.apply {
        attributes["Main-Class"] = "cubicchunks.converter.gui.GuiMain"
    }
}
/*
val javadocJar by tasks.creating(Jar::class) {
    classifier = "javadoc"
    from(tasks["javadoc"])
}*/
val sourcesJar by tasks.creating(Jar::class) {
    classifier = "sources"
    from(sourceSets["main"].java.srcDirs)
}

val headlessJar by tasks.creating(Jar::class) {
    classifier = "headless"
    from(sourceSets["main"].java.srcDirs)
    exclude("cubicchunks/converter/gui")
    manifest.apply {
        attributes["Main-Class"] = "cubicchunks.converter.headless.HeadlessMain"
    }
}

val headlessShadowJar by tasks.creating(ShadowJar::class) {
    dependsOn(headlessJar)
    manifest.inheritFrom(headlessJar.manifest)
    from(java.sourceSets["main"].output)
    configurations.add(project.configurations.runtime)
    exclude("META-INF/INDEX.LIST", "META-INF/*.SF", "META-INF/*.DSA", "META-INF/*.RSA", "cubicchunks/converter/gui")
    classifier = "headless-all"
}

tasks["build"].dependsOn(shadowJar, headlessShadowJar)

val signing: SigningExtension by extensions
signing.apply {
    isRequired = false
    // isRequired = gradle.taskGraph.hasTask("uploadArchives")
    sign(configurations.archives)
}

// based on:
// https://github.com/Ordinastie/MalisisCore/blob/30d8efcfd047ac9e9bc75dfb76642bd5977f0305/build.gradle#L204-L256
// https://github.com/gradle/kotlin-dsl/blob/201534f53d93660c273e09f768557220d33810a9/samples/maven-plugin/build.gradle.kts#L10-L44
val uploadArchives: Upload by tasks
uploadArchives.apply {
    repositories {
        withConvention(MavenRepositoryHandlerConvention::class) {
            mavenDeployer {
                // Sign Maven POM
                beforeDeployment {
                    signing.signPom(this)
                }

                val username = if (project.hasProperty("sonatypeUsername")) project.properties["sonatypeUsername"] else System.getenv("sonatypeUsername")
                val password = if (project.hasProperty("sonatypePassword")) project.properties["sonatypePassword"] else System.getenv("sonatypePassword")

                withGroovyBuilder {
                    "snapshotRepository"("url" to "https://oss.sonatype.org/content/repositories/snapshots") {
                        "authentication"("userName" to username, "password" to password)
                    }

                    "repository"("url" to "https://oss.sonatype.org/service/local/staging/deploy/maven2") {
                        "authentication"("userName" to username, "password" to password)
                    }
                }

                // Maven POM generation
                pom.project {
                    withGroovyBuilder {
                        "name"(projectName)
                        "artifactId"(base.archivesBaseName.toLowerCase())
                        "packaging"("jar")
                        "url"("https://github.com/OpenCubicChunks/CubicChunksConverter")
                        "description"("Save converter from vanilla Minecraft to cubic chunks")


                        "scm" {
                            "connection"("scm:git:git://github.com/OpenCubicChunks/CubicChunksConverter.git")
                            "developerConnection"("scm:git:ssh://git@github.com:OpenCubicChunks/CubicChunksConverter.git")
                            "url"("https://github.com/OpenCubicChunks/CubicChunksConverter")
                        }

                        "licenses" {
                            "license" {
                                "name"("The MIT License")
                                "url"("http://www.tldrlegal.com/license/mit-license")
                                "distribution"("repo")
                            }
                        }

                        "developers" {
                            "developer" {
                                "id"("Barteks2x")
                                "name"("Barteks2x")
                            }
                        }

                        "issueManagement" {
                            "system"("github")
                            "url"("https://github.com/OpenCubicChunks/CubicChunksConverter/issues")
                        }
                    }
                }
            }
        }
    }
}

// tasks must be before artifacts, don't change the order
artifacts {
    withGroovyBuilder {
        "archives"(jar, shadowJar, headlessJar, headlessShadowJar, sourcesJar)
    }
}

//returns version string according to this: http://semver.org/
//format: MAJOR.MINOR.PATCH
fun getProjectVersion(): String {
    try {
        val git = Grgit.open()
        val describe = DescribeOp(git.repository).call()
        val branch = getGitBranch(git)
        val snapshotSuffix = if (project.hasProperty("doRelease")) "" else "-SNAPSHOT"
        return getVersion_do(describe, branch) + snapshotSuffix
    } catch (ex: RuntimeException) {
        logger.error("Unknown error when accessing git repository! Are you sure the git repository exists?", ex)
        return String.format("v9999-9999-gffffff", "localbuild")
    }
}

fun getGitBranch(git: Grgit): String {
    var branch: String = git.branch.current.name
    if (branch.equals("HEAD")) {
        branch = when {
            System.getenv("TRAVIS_BRANCH")?.isEmpty() == false -> // travis
                System.getenv("TRAVIS_BRANCH")
            System.getenv("GIT_BRANCH")?.isEmpty() == false -> // jenkins
                System.getenv("GIT_BRANCH")
            System.getenv("BRANCH_NAME")?.isEmpty() == false -> // ??? another jenkins alternative?
                System.getenv("BRANCH_NAME")
            else -> throw RuntimeException("Found HEAD branch! This is most likely caused by detached head state! Will assume unknown version!")
        }
    }

    if (branch.startsWith("origin/")) {
        branch = branch.substring("origin/".length)
    }
    return branch
}

fun getVersion_do(describe: String, branch: String): String {

    val versionMinorFreeze = project.property("versionMinorFreeze") as String

    //branch "master" is not appended to version string, everything else is
    //only builds from "master" branch will actually use the correct versioning
    //but it allows to distinguish between builds from different branches even if version number is the same
    val branchSuffix = if (branch == "master") "" else ("-" + branch.replace("[^a-zA-Z0-9.-]", "_"))

    val baseVersionRegex = "v[0-9]+"
    val unknownVersion = String.format("UNKNOWN_VERSION%s", branchSuffix)
    if (!describe.contains('-')) {
        //is it the "vX" format?
        if (describe.matches(Regex(baseVersionRegex))) {
            return String.format("%s.0.0%s", describe, branchSuffix)
        }
        logger.error("Git describe information: \"$describe\" in unknown/incorrect format")
        return unknownVersion
    }
    //Describe format: vX-build-hash
    val parts = describe.split("-")
    if (!parts[0].matches(Regex(baseVersionRegex))) {
        logger.error("Git describe information: \"$describe\" in unknown/incorrect format")
        return unknownVersion
    }
    if (!parts[1].matches(Regex("[0-9]+"))) {
        logger.error("Git describe information: \"$describe\" in unknown/incorrect format")
        return unknownVersion
    }
    val apiVersion = parts[0].substring(1)
    //next we have commit-since-tag
    val commitSinceTag = Integer.parseInt(parts[1])

    val minorFreeze = if (versionMinorFreeze.isEmpty()) -1 else Integer.parseInt(versionMinorFreeze)

    val minor = if (minorFreeze < 0) commitSinceTag else minorFreeze
    val patch = if (minorFreeze < 0) 0 else (commitSinceTag - minorFreeze)

    val version = String.format("%s.%d.%d%s", apiVersion, minor, patch, branchSuffix)
    return version
}
